#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ViewEngine.h"
#include "ApplicationConfig.h"

#if defined(Q_OS_ANDROID)
    #include <QJniObject>
    #include <QJniEnvironment>
    #include <QJsonDocument>
    #include <QJsonValue>
    #include <QJsonArray>
    #include <QJsonObject>
    #include "AndroidJNIManager.h"
#elif defined(Q_OS_WINDOWS)
    // #include "WinWifiManager.h"
    #include "SingletonApplication.h"
#endif
// #include "ThemeManager.h"
// #include "UsbManager.h"
// #include "DevicesManager.h"
// #include "Translator.h"

#include "SqlManager.h"
#include <QStandardPaths>
#include <QDir>
#include "ZeroLogger.h"
#include <QTimer>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <QtConcurrent>
#include <openssl/ssl.h>

#include <QTcpSocket>

static quint16 crc16_xmodem(const QByteArray& data)
{
    quint16 crc = 0x0000;
    for (unsigned char b : data)
    {
        crc ^= (quint16)b << 8;
        for (int i = 0; i < 8; ++i)
            crc = (crc & 0x8000) ? (crc << 1) ^ 0x1021 : (crc << 1);
    }
    return crc;
}

static QByteArray buildReadUdmFrame()
{
    QByteArray f;
    f.resize(20);
    auto put16 = [&](int off, quint16 v) {
        f[off]     = v & 0xFF;
        f[off + 1] = (v >> 8) & 0xFF;
    };

    put16(0, 0x0004);   // packetType=4, packetC/T=0, packetCNT=0
    put16(2, 0x0005);   // packetSIZE=5 -> 20 字节
    put16(4, 0x0000);   // StreamID
    put16(6, 0x0001);   // FrameEOF=1, CmdNUM=0
    put16(8, 0x0000);   // PAD/OUI
    put16(10, 0x0001);  // RW=1 读
    // 12-13 留空，最后填 CRC
    put16(14, 0x0406);  // PacketClassCode=6, BurstLength=64
    f[16] = 0x80;
    f[17] = 0xFF;
    f[18] = 0xFF;
    f[19] = 0xFF;  // 地址 0xFFFFFF80

    QByteArray crcArea = f.left(12) + f.mid(14, 2);
    put16(12, crc16_xmodem(crcArea));  // 小端写入

    return f;
}

void connectProbe()
{
    static QTcpSocket* tcp_con = new QTcpSocket();

    // 先注册收包回调，再连接，避免回包比回调先到
    static QByteArray g_rxBuf;  // 累积缓冲

    QObject::connect(tcp_con, &QTcpSocket::readyRead, [&]() {
        g_rxBuf += tcp_con->readAll();
        qDebug() << "readyRead, buf size =" << g_rxBuf.size();

        while (g_rxBuf.size() >= 16)
        {
            quint16 sizeRaw = (quint8)g_rxBuf[2] | ((quint8)g_rxBuf[3] << 8);
            int     total   = sizeRaw * 4;
            if (g_rxBuf.size() < total) break;  // 没到齐，继续等

            QByteArray frame = g_rxBuf.left(total);
            g_rxBuf.remove(0, total);

            // CRC 校验（覆盖 [0..11]+[14..15]）
            QByteArray crcArea = frame.left(12) + frame.mid(14, 2);
            quint16    calc    = crc16_xmodem(crcArea);
            quint16    recv    = (quint8)frame[12] | ((quint8)frame[13] << 8);
            if (calc != recv)
            {
                qDebug() << "CRC 错误，丢弃整包";
                continue;
            }

            quint16 rw        = (quint8)frame[10] | ((quint8)frame[11] << 8);
            quint16 classBl   = (quint8)frame[14] | ((quint8)frame[15] << 8);
            quint8  classCode = classBl & 0x0F;
            quint16 burst     = classBl >> 4;

            qDebug() << "RX: RW=" << rw << " Class=" << classCode << " Burst=" << burst;

            quint32    addr = (quint8)frame[16] | ((quint8)frame[17] << 8) | ((quint8)frame[18] << 16) | ((quint8)frame[19] << 24);
            QByteArray udm  = frame.mid(20, burst * 4);  // 256 字节

            qDebug() << "Addr =" << QString::number(addr, 16);
            qDebug() << "UDM  =" << udm.toHex(' ');

            // 顺便解析字段（按文档 3.2 偏移）
            auto field = [&](int off, int len) -> QString {
                QByteArray raw = udm.mid(off, len);
                int        end = raw.indexOf('\0');
                if (end >= 0) raw.truncate(end);  // 遇到第一个 \0 就截断
                return QString::fromLatin1(raw);
            };
            qDebug() << "ProductMFR  =" << field(10, 8);
            qDebug() << "ProductName =" << field(18, 8);
            qDebug() << "ProductSN   =" << field(26, 16);
            qDebug() << "DeviceID    =" << field(42, 16);
            qDebug() << "DeviceSN    =" << field(58, 32);
            qDebug() << "DeviceVer   =" << field(90, 40);
        }
    });

    // 连接
    tcp_con->connectToHost("192.168.0.10", 5061);

    if (tcp_con->waitForConnected(3000))
    {
        qDebug() << "Connected!";

        // ★★★ 关键：发送读 UDM 请求 ★★★
        QByteArray frame = buildReadUdmFrame();
        qDebug() << "TX:" << frame.toHex(' ');
        tcp_con->write(frame);
        tcp_con->flush();
    }
    else
    {
        qDebug() << "Connect failed:" << tcp_con->errorString();
    }
}

void fetchPhoneCode()
{
    const QString caPath = QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation))
                               .filePath("cacert.pem");
    if (!QFile::exists(caPath))
    {
        if (!QFile::copy(":/config/Android/cacert.pem", caPath))
        {
            qDebug() << "CA 复制失败";
            return;
        }
        QFile::setPermissions(caPath, QFile::ReadOwner | QFile::WriteOwner);
    }
    qDebug() << "CA exists:" << QFile::exists(caPath) << caPath;

    httplib::SSLClient cli("zscs.imeik.com");
    cli.set_connection_timeout(10, 0);
    cli.set_read_timeout(10, 0);
    cli.set_ca_cert_path(caPath.toStdString().c_str());

    cli.set_error_logger([](const httplib::Error& err, const httplib::Request*) {
        qDebug() << "httplib error:" << httplib::to_string(err).c_str();
    });

    httplib::Headers headers = {
        {"User-Agent", "Mozilla/5.0"},
        {"Accept", "application/json"}};

    auto res = cli.Get("/app/V0/phoneCode?phone=18294821095&type=1", headers);

    if (res && res->status == 200)
    {
        qDebug() << "响应:" << QString::fromStdString(res->body);
    }
    else
    {
        qDebug() << "失败，状态码:" << (res ? res->status : -1);
    }
}

int main(int argc, char* argv[])
{
#if defined(Q_OS_WINDOWS)
    // UsbManager usbManager{};
    // for (const auto& [_k, _v] : usbManager.devicesList())
    // {
    //     qInfo() << _k << ":" << _v;
    // }
    SingletonApplication::instance()->init();
#elif defined(Q_OS_ANDROID)
    QtConcurrent::run([]() {
        // fetchPhoneCode();
    });
#endif
    ApplicationConfig::instance()->init();
    QGuiApplication app{argc, argv};
    // qDebug() << ThemeManager::create(nullptr, nullptr)->currentTheme();
    QQmlApplicationEngine engine{};
    // Translator::create(&engine, nullptr)->setLanguage(":/i18n/qml_en.qm");
    ViewEngine::instance(engine)->init();
    // ZeroLogger::instance()->init(QDir{QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)}.filePath("log/SonixLog_1.txt").toStdString());
    // spdlog::set_level(spdlog::level::trace);
    // spdlog::trace("---=======1");
    // SPDLOG_WARN("---=======2:{}", "String");
    // SPDLOG_ERROR("---=======3");
    // DevicesManager::create(nullptr, nullptr)->refreshDevicesList();
    // qWarning() << QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);

#if false
    SqlManager::instance()->setDatabaseName(QPair<QString, DataBasePathType>("qrc:/config/dataBase/UAS.db", DataBasePathType::ResourcePath));
    QSqlQuery query = SqlManager::instance()->executeSql<QSqlQuery>("qrc:/config/dataBase/UAS.db", "select * from tPartName");
    while (query.next())
    {
        for (int i = 0; i < query.record().count(); ++i)
        {
            qInfo() << query.record().fieldName(i) << ":" << query.value(i).toString();
        }
    }
#endif

#if defined(Q_OS_ANDROID)

    #if true
    AndroidJNIManager* androidJNIManager{new AndroidJNIManager{}};
    androidJNIManager->setActivityUrl("com/sonixbeauty/module/JWifiManager");
    QJniObject            result{androidJNIManager->callJNIMethod<QJniObject>("getWifiList", "()Ljava/lang/String;")};
    QMap<QString, quint8> wifiViewMap{};
    QJsonDocument         doc{QJsonDocument::fromJson(result.toString().toUtf8())};
    for (const QJsonValue& value : doc.array())
    {
        wifiViewMap[value.toObject()["ssid"].toString()] = static_cast<quint8>(value.toObject()["level"].toInt());
    }
    for (const auto& [k, v] : wifiViewMap.toStdMap())
    {
        // qInfo() << k << ":" << v;
    }

    // qInfo() << "currentWifiName ->" << androidJNIManager->callJNIMethod<QJniObject>("currentWifiName", "()Ljava/lang/String;").toString();

    // QTimer::singleShot(5000, [&androidJNIManager]() {
    //     androidJNIManager->callJNIMethod<void>("connectToWifi", "(Ljava/lang/String;Ljava/lang/String;)V", QJniObject::fromString("US06-9C50D101E27E").object<jstring>(), QJniObject::fromString("12345678").object<jstring>());
    // });

    QTimer::singleShot(10000, [&androidJNIManager]() {
        androidJNIManager->callJNIMethod<void>("connectToWifi", "(Ljava/lang/String;Ljava/lang/String;)V", QJniObject::fromString("US06-9C50D101E3B4").object<jstring>(), QJniObject::fromString("12345678").object<jstring>());
    });

    QTimer::singleShot(15000, [&androidJNIManager]() {
        connectProbe();
    });

    // QTimer::singleShot(20000, [&androidJNIManager]() {
    //     androidJNIManager->callJNIMethod<void>("disconnectWifi", "()V");
    // });
    #endif
    QNativeInterface::QAndroidApplication::hideSplashScreen(0);
#endif
    return QGuiApplication::exec();
}
