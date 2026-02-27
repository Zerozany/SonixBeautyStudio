#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ViewEngine.h"
// #include "Translator.h"
// #include "ZeroLogger.h"
// #include <QDir>
// #include <QStandardPaths>
#include "ApplicationConfig.h"
#include "SingletonApplication.h"

#if defined(Q_OS_ANDROID)
    #include <QJniObject>
    #include <QJniEnvironment>
    #include "AndroidWifiManager.h"
#elif defined(Q_OS_WINDOWS)
    #include "WinWifiManager.h"
#endif
// #include "ThemeManager.h"
// #include <libusb-1.0/libusb.h>

int main(int argc, char* argv[])
{
#if defined(Q_OS_WINDOWS)
    SingletonApplication::instance()->init();
    WinWifiManager::instance()->getWifiList();

#endif
    ApplicationConfig::instance()->init();
    QGuiApplication app{argc, argv};
    // qDebug() << ThemeManager::create(nullptr, nullptr)->currentTheme();
    QQmlApplicationEngine engine{};
    // Translator::create(&engine, nullptr)->setLanguage(":/i18n/qml_zh_CN.qm");
    ViewEngine::instance(engine)->init();
    // ZeroLogger::init(QDir{QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)}.filePath("log/SonixLog_1.txt").toStdString());
    // ZeroLogger::setLevel(spdlog::level::warn);
#if defined(Q_OS_ANDROID)
    // AndroidWifiManager androidWifiManager{"com/sonixbeauty/module/JWifiManager"};
    // qDebug() << "currentWifiName:" << androidWifiManager.currentWifiName("currentWifiName");
    // androidWifiManager.connectToWifi("connectToWifi", "ChinaNet-zero821", "18583943303");
    // for (const auto& [k, v] : androidWifiManager.getWifiList("getWifiList").toStdMap())
    // {
    //     qDebug() << k << ":" << v;
    // }
    QNativeInterface::QAndroidApplication::hideSplashScreen(0);
#endif
    return QGuiApplication::exec();
}
