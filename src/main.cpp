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
#include <QThread>
#include <QtConcurrent>
#include <openssl/ssl.h>

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
    SSL_library_init();
    SSL_load_error_strings();
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
        fetchPhoneCode();
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

    qInfo() << "currentWifiName ->" << androidJNIManager->callJNIMethod<QJniObject>("currentWifiName", "()Ljava/lang/String;").toString();

    // QTimer::singleShot(5000, [&androidJNIManager]() {
    //     androidJNIManager->callJNIMethod<void>("connectToWifi", "(Ljava/lang/String;Ljava/lang/String;)V", QJniObject::fromString("US06-9C50D101E27E").object<jstring>(), QJniObject::fromString("12345678").object<jstring>());
    // });

    // QTimer::singleShot(10000, [&androidJNIManager]() {
    //     androidJNIManager->callJNIMethod<void>("connectToWifi", "(Ljava/lang/String;Ljava/lang/String;)V", QJniObject::fromString("US06-9C50D101E3B4").object<jstring>(), QJniObject::fromString("12345678").object<jstring>());
    // });

    // QTimer::singleShot(20000, [&androidJNIManager]() {
    //     androidJNIManager->callJNIMethod<void>("disconnectWifi", "()V");
    // });
    #endif
    QNativeInterface::QAndroidApplication::hideSplashScreen(0);
#endif
    return QGuiApplication::exec();
}
