#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ViewEngine.h"
#include "ApplicationConfig.h"

#if defined(Q_OS_ANDROID)

#elif defined(Q_OS_WINDOWS)
    #include "SingletonApplication.h"
#endif
// #include "ThemeManager.h"
// #include "UsbManager.h"
// #include "Translator.h"

#include "SqlManager.h"
#include <QStandardPaths>
#include <QDir>
// #include "SpdLogger.h"
// #include "LoginManager.h"

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
    // SpdLogger::instance()->init(QDir{QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)}.filePath("log/SonixLog_1.txt").toStdString());
    // spdlog::set_level(spdlog::level::trace);
    // SPDLOG_WARN("---=======2:{}", "String");
    // SPDLOG_ERROR("---=======3");

#if defined(Q_OS_ANDROID)
    QNativeInterface::QAndroidApplication::hideSplashScreen(0);
#endif
    return QGuiApplication::exec();
}
