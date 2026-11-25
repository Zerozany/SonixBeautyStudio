#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ApplicationManager.h"
#include "ThirdManager.h"
#include "QmlEngineManager.h"

#if defined(Q_OS_ANDROID)

#elif defined(Q_OS_WINDOWS)
// #include "UsbManager.h"
#endif

auto main(int _argc, char* _argv[]) -> int
{
#if defined(Q_OS_WINDOWS)
    // UsbManager usbManager{};
    // for (const auto& [_k, _v] : usbManager.devicesList())
    // {
    //     qInfo() << _k << ":" << _v;
    // }
#elif defined(Q_OS_ANDROID)

#endif
    ApplicationManager::instance()->init();
    QGuiApplication app{_argc, _argv};
    ThirdManager::instance()->init();
    QQmlApplicationEngine engine{};
    QmlEngineManager::instance(engine)->init();

#if defined(Q_OS_ANDROID)
    QNativeInterface::QAndroidApplication::hideSplashScreen(0);
#endif
    return QGuiApplication::exec();
}
