#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "QmlEngineManager.h"
#include "ApplicationManager.h"

#if defined(Q_OS_ANDROID)

#elif defined(Q_OS_WINDOWS)
    #include "SingletonApplication.h"
// #include "UsbManager.h"
#endif

#include "LoggerMacro.hpp"
#include "LogConfig.h"

auto main(int argc, char* argv[]) -> int
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

    ApplicationManager::instance()->init();
    QGuiApplication       app{argc, argv};
    QQmlApplicationEngine engine{};
    QmlEngineManager::instance(engine)->init();

    LogManager::instance()->init(LogConfig::instance()->logSavePath().toStdString());
    LogManager::instance()->set_level(spdlog::level::trace);

    LOG_TRACE("---{}---", "LOG_TRACE");
    LOG_INFO("---{}---", "LOG_INFO");
    LOG_DEBUG("---{}---", "LOG_DEBUG");
    LOG_WARN("---{}---", "LOG_WARN");
    LOG_ERROR("---{}---", "LOG_ERROR");
    LOG_CRITICAL("---{}---", "LOG_CRITICAL");

#if defined(Q_OS_ANDROID)
    QNativeInterface::QAndroidApplication::hideSplashScreen(0);
#endif
    return QGuiApplication::exec();
}
