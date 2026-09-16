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

// 写 ResetDevice 寄存器 0xFFFFFFC0：0=冻结，1=取消冻结
static QByteArray buildWriteResetDeviceFrame(quint32 value)
{
    QByteArray f;
    f.resize(24);
    auto put16 = [&](int off, quint16 v) {
        f[off]     = v & 0xFF;
        f[off + 1] = (v >> 8) & 0xFF;
    };

    put16(0, 0x0004);   // packetType=4, packetC/T=0, packetCNT=0
    put16(2, 0x0006);   // packetSIZE=6 -> 24 字节
    put16(4, 0x0000);   // StreamID
    put16(6, 0x0001);   // FrameEOF=1, CmdNUM=0
    put16(8, 0x0000);   // PAD/OUI
    put16(10, 0x0000);  // RW=0 写（不回包）
    // 12-13 留空，最后填 CRC
    put16(14, 0x0104);  // PacketClassCode=4(D32), BurstLength=1（1 个 4B 单元）

    // 地址 0xFFFFFFC0（小端）
    f[16] = 0xC0;
    f[17] = 0xFF;
    f[18] = 0xFF;
    f[19] = 0xFF;

    // 数据 4 字节（小端）
    f[20] = value & 0xFF;
    f[21] = (value >> 8) & 0xFF;
    f[22] = (value >> 16) & 0xFF;
    f[23] = (value >> 24) & 0xFF;

    QByteArray crcArea = f.left(12) + f.mid(14, 2);
    put16(12, crc16_xmodem(crcArea));

    return f;
}

#if false  // 单次数发送
void connectProbe()
{
    static QTcpSocket* tcp_con = nullptr;
    static QByteArray  g_rxBuf;

    if (!tcp_con)
    {
        tcp_con = new QTcpSocket();

        QObject::connect(tcp_con, &QTcpSocket::readyRead, []() {
            g_rxBuf += tcp_con->readAll();
            qDebug() << "readyRead, buf size =" << g_rxBuf.size();

            while (g_rxBuf.size() >= 16)
            {
                // packetSIZE 表示整包占多少个 32bit word
                quint16 sizeRaw = (quint8)g_rxBuf[2] | ((quint8)g_rxBuf[3] << 8);
                int     total   = sizeRaw * 4;
                if (total < 20)
                {
                    qDebug() << "包长度异常:" << total;
                    break;
                }
                if (g_rxBuf.size() < total)
                    break;  // 整帧没到齐，等下次

                QByteArray frame = g_rxBuf.left(total);
                g_rxBuf.remove(0, total);

                // CRC 校验（覆盖 [0..11] + [14..15]）
                QByteArray crcArea = frame.left(12) + frame.mid(14, 2);
                quint16    calc    = crc16_xmodem(crcArea);
                quint16    recv    = (quint8)frame[12] | ((quint8)frame[13] << 8);
                if (calc != recv)
                {
                    qDebug() << "CRC 错误，丢弃整包";
                    continue;
                }

                quint16 classBl   = (quint8)frame[14] | ((quint8)frame[15] << 8);
                quint16 burst     = classBl >> 4;
                quint8  classCode = classBl & 0x0F;
                quint16 rw        = (quint8)frame[10] | ((quint8)frame[11] << 8);

                qDebug() << "RX: RW=" << rw << " Class=" << classCode << " Burst=" << burst;

                quint32    addr = (quint8)frame[16] | ((quint8)frame[17] << 8) | ((quint8)frame[18] << 16) | ((quint8)frame[19] << 24);
                QByteArray udm  = frame.mid(20, burst * 4);  // 头部固定 20 字节

                qDebug() << "Addr =" << QString::number(addr, 16);
                qDebug() << "UDM  =" << udm.toHex(' ');

                auto field = [&](int off, int len) -> QString {
                    QByteArray raw = udm.mid(off, len);
                    int        end = raw.indexOf('\0');
                    if (end >= 0) raw.truncate(end);
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
    }

    tcp_con->connectToHost("192.168.0.10", 5061);

    if (tcp_con->waitForConnected(3000))
    {
        qDebug() << "Connected!";
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
#endif

#if true  // 持续发送
void connectProbe()
{
    static QTcpSocket* tcp_con = nullptr;
    static QByteArray  g_rxBuf;

    if (!tcp_con)
    {
        tcp_con = new QTcpSocket();

        QObject::connect(tcp_con, &QTcpSocket::readyRead, []() {
            g_rxBuf += tcp_con->readAll();
            qDebug() << "readyRead, buf size =" << g_rxBuf.size();

            while (g_rxBuf.size() >= 16)
            {
                quint16 sizeRaw = (quint8)g_rxBuf[2] | ((quint8)g_rxBuf[3] << 8);
                int     total   = sizeRaw * 4;
                if (total < 20)
                {
                    qDebug() << "包长度异常:" << total;
                    break;
                }
                if (g_rxBuf.size() < total)
                    break;  // 整帧没到齐，等下次

                QByteArray frame = g_rxBuf.left(total);
                g_rxBuf.remove(0, total);

                QByteArray crcArea = frame.left(12) + frame.mid(14, 2);
                quint16    calc    = crc16_xmodem(crcArea);
                quint16    recv    = (quint8)frame[12] | ((quint8)frame[13] << 8);
                if (calc != recv)
                {
                    qDebug() << "CRC 错误，丢弃整包";
                    continue;
                }

                quint16 classBl   = (quint8)frame[14] | ((quint8)frame[15] << 8);
                quint16 burst     = classBl >> 4;
                quint8  classCode = classBl & 0x0F;
                quint16 rw        = (quint8)frame[10] | ((quint8)frame[11] << 8);

                qDebug() << "RX: RW=" << rw << " Class=" << classCode << " Burst=" << burst;

                quint32    addr = (quint8)frame[16] | ((quint8)frame[17] << 8) | ((quint8)frame[18] << 16) | ((quint8)frame[19] << 24);
                QByteArray udm  = frame.mid(20, burst * 4);

                qDebug() << "Addr =" << QString::number(addr, 16);
                qDebug() << "UDM  =" << udm.toHex(' ');

                auto field = [&](int off, int len) -> QString {
                    QByteArray raw = udm.mid(off, len);
                    int        end = raw.indexOf('\0');
                    if (end >= 0) raw.truncate(end);
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

        // ---- 定时轮询：每 1 秒发一次读请求 ----
        QTimer* pollTimer = new QTimer(tcp_con);
        QObject::connect(pollTimer, &QTimer::timeout, []() {
            if (tcp_con->state() == QAbstractSocket::ConnectedState)
            {
                QByteArray frame = buildReadUdmFrame();
                tcp_con->write(frame);
                tcp_con->flush();
                qDebug() << "TX:" << frame.toHex(' ');
            }
        });
        pollTimer->start(1000);  // 1000 ms，想快就改小
    }

    tcp_con->connectToHost("192.168.0.10", 5061);

    if (tcp_con->waitForConnected(3000))
    {
        qDebug() << "Connected!";
    }
    else
    {
        qDebug() << "Connect failed:" << tcp_con->errorString();
    }
}
#endif

#if false  // 交替冻结
void connectProbe()
{
    static QTcpSocket* tcp_con = nullptr;
    static QByteArray  g_rxBuf;
    static int         pollCount = 0;
    static bool        frozen    = true;  // 连接后先冻结

    if (!tcp_con)
    {
        tcp_con = new QTcpSocket();

        QObject::connect(tcp_con, &QTcpSocket::readyRead, []() {
            g_rxBuf += tcp_con->readAll();
            qDebug() << "readyRead, buf size =" << g_rxBuf.size();

            while (g_rxBuf.size() >= 16)
            {
                quint16 sizeRaw = (quint8)g_rxBuf[2] | ((quint8)g_rxBuf[3] << 8);
                int     total   = sizeRaw * 4;
                if (total < 20)
                {
                    qDebug() << "包长度异常:" << total;
                    break;
                }
                if (g_rxBuf.size() < total)
                    break;

                QByteArray frame = g_rxBuf.left(total);
                g_rxBuf.remove(0, total);

                QByteArray crcArea = frame.left(12) + frame.mid(14, 2);
                quint16    calc    = crc16_xmodem(crcArea);
                quint16    recv    = (quint8)frame[12] | ((quint8)frame[13] << 8);
                if (calc != recv)
                {
                    qDebug() << "CRC 错误，丢弃整包";
                    continue;
                }

                quint16 classBl   = (quint8)frame[14] | ((quint8)frame[15] << 8);
                quint16 burst     = classBl >> 4;
                quint8  classCode = classBl & 0x0F;
                quint16 rw        = (quint8)frame[10] | ((quint8)frame[11] << 8);

                qDebug() << "RX: RW=" << rw << " Class=" << classCode << " Burst=" << burst;

                quint32    addr = (quint8)frame[16] | ((quint8)frame[17] << 8) | ((quint8)frame[18] << 16) | ((quint8)frame[19] << 24);
                QByteArray udm  = frame.mid(20, burst * 4);

                qDebug() << "Addr =" << QString::number(addr, 16);
                qDebug() << "UDM  =" << udm.toHex(' ');

                auto field = [&](int off, int len) -> QString {
                    QByteArray raw = udm.mid(off, len);
                    int        end = raw.indexOf('\0');
                    if (end >= 0) raw.truncate(end);
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

        // ---- 定时轮询：每 1 秒一次 ----
        QTimer* pollTimer = new QTimer(tcp_con);
        QObject::connect(pollTimer, &QTimer::timeout, []() {
            if (tcp_con->state() != QAbstractSocket::ConnectedState)
                return;

            // 1) 每 10 次切换一次冻结/解冻
            if (pollCount > 0 && pollCount % 10 == 0)
            {
                frozen           = !frozen;
                quint32    value = frozen ? 0x00000000 : 0x00000001;  // 0 冻结 / 1 解冻
                QByteArray fz    = buildWriteResetDeviceFrame(value);
                tcp_con->write(fz);
                tcp_con->flush();
                qDebug() << "TX(ResetDevice):" << fz.toHex(' ')
                         << (frozen ? "-> 冻结" : "-> 解冻");
            }

            // 2) 发读 UDM 请求
            QByteArray frame = buildReadUdmFrame();
            tcp_con->write(frame);
            tcp_con->flush();
            qDebug() << "TX(UDM):" << frame.toHex(' ')
                     << " pollCount =" << pollCount;

            ++pollCount;
        });
        pollTimer->start(1000);
    }

    tcp_con->connectToHost("192.168.0.10", 5061);

    if (tcp_con->waitForConnected(3000))
    {
        qDebug() << "Connected!";

        // 连接后先冻结一次
        QByteArray fz = buildWriteResetDeviceFrame(0x00000000);
        tcp_con->write(fz);
        tcp_con->flush();
        frozen = true;
        qDebug() << "TX(ResetDevice):" << fz.toHex(' ') << "-> 初始冻结";
    }
    else
    {
        qDebug() << "Connect failed:" << tcp_con->errorString();
    }
}
#endif

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
        qDebug() << "状态码:" << res->status;
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
    QtConcurrent::run([]() {
        // fetchPhoneCode();
    });
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

    QTimer::singleShot(3000, [&androidJNIManager]() {
        androidJNIManager->callJNIMethod<void>("connectToWifi", "(Ljava/lang/String;Ljava/lang/String;)V", QJniObject::fromString("US06-9C50D101E27E").object<jstring>(), QJniObject::fromString("12345678").object<jstring>());
    });

    // QTimer::singleShot(3000, [&androidJNIManager]() {
    //     androidJNIManager->callJNIMethod<void>("connectToWifi", "(Ljava/lang/String;Ljava/lang/String;)V", QJniObject::fromString("US06-9C50D101E3B4").object<jstring>(), QJniObject::fromString("12345678").object<jstring>());
    // });

    QTimer::singleShot(7000, [&androidJNIManager]() {
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
