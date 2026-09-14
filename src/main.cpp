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
// #include <spdlog/spdlog.h>              // spdlog 核心库
// #include <spdlog/sinks/android_sink.h>  // Android sink 实现

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
    // ZeroLogger::init(QDir{QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)}.filePath("log/SonixLog_1.txt").toStdString());
    // ZeroLogger::setLevel(spdlog::level::trace);
    // ZeroLogger::trace("---=======");
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
    // auto android_logger = spdlog::android_logger_mt("android", "spdlog");
    // android_logger->critical("Use \"adb shell logcat\" to view this message.");
    // android_logger->set_level(spdlog::level::trace);
    // spdlog::set_default_logger(android_logger);
    // spdlog::debug("XXXXXXX=======");

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
        qInfo() << k << ":" << v;
    }
    androidJNIManager->callJNIMethod<void>("connectToWifi", "(Ljava/lang/String;Ljava/lang/String;)V", QJniObject::fromString("US06-9C50D101E3B4").object<jstring>(), QJniObject::fromString("12345678").object<jstring>());
    // qInfo() << androidJNIManager->callJNIMethod<QJniObject>("currentWifiName", "()Ljava/lang/String;").toString();

    // QTimer::singleShot(3000, [&androidJNIManager]() {
    //     androidJNIManager->callJNIMethod<void>("disconnectWifi", "()V");
    //     QNativeInterface::QAndroidApplication::hideSplashScreen(0);
    // });
    #endif
    QNativeInterface::QAndroidApplication::hideSplashScreen(0);
#endif
    return QGuiApplication::exec();
}
