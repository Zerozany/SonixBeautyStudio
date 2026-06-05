#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ViewEngine.h"
// #include "Translator.h"
// #include "ZeroLogger.h"
#include "ApplicationConfig.h"
#include "SingletonApplication.h"

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
#endif
// #include "ThemeManager.h"
// #include "UsbManager.h"
// #include "DevicesManager.h"
#include "SqlManager.h"
#include <QStandardPaths>
#include <QDir>

int main(int argc, char* argv[])
{
    // UsbManager usbManager{};
    // for (const auto& [_k, _v] : usbManager.devicesList())
    // {
    //     qDebug() << _k << ":" << _v;
    // }

#if defined(Q_OS_WINDOWS)
    SingletonApplication::instance()->init();
#endif
    ApplicationConfig::instance()->init();
    QGuiApplication app{argc, argv};
    // qDebug() << ThemeManager::create(nullptr, nullptr)->currentTheme();
    QQmlApplicationEngine engine{};
    // Translator::create(&engine, nullptr)->setLanguage(":/i18n/qml_zh_CN.qm");
    ViewEngine::instance(engine)->init();
    // ZeroLogger::init(QDir{QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)}.filePath("log/SonixLog_1.txt").toStdString());
    // ZeroLogger::setLevel(spdlog::level::trace);
    // DevicesManager::create(nullptr, nullptr)->refreshDevicesList();
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
    AndroidJNIManager::instance()->setActivityUrl("com/sonixbeauty/module/JWifiManager");
    #if false
    QJniObject            result{AndroidJNIManager::instance()->callJNIMethod<QJniObject>("getWifiList", "()Ljava/lang/String;")};
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
    #elif true
    // AndroidJNIManager::instance()->callJNIMethod<void>("connectToWifi", "(Ljava/lang/String;Ljava/lang/String;)V", QJniObject::fromString("US06-9C50D101E1B2").object<jstring>(), QJniObject::fromString("12345678").object<jstring>());
    qInfo() << AndroidJNIManager::instance()->callJNIMethod<QJniObject>("currentWifiName", "()Ljava/lang/String;").toString();
    #endif
    QNativeInterface::QAndroidApplication::hideSplashScreen(0);
#endif
    return QGuiApplication::exec();
}
