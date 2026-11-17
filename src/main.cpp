#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ViewManager.h"
#include "ApplicationManager.h"

#if defined(Q_OS_ANDROID)

#elif defined(Q_OS_WINDOWS)
    #include "SingletonApplication.h"
// #include "UsbManager.h"
#endif

// #include <QStandardPaths>
// #include <QDir>
// #include "SpdLogger.h"
#include "MeasureKits.h"
#include "MeasureConfig.hpp"

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
    MeasureKits measureKits{};
    qDebug() << measureKits.measure(Department::Obstetrics::BiparietalDiameter, 7.52);
    qDebug() << measureKits.measure(Department::Obstetrics::FemurLength, 5.24);
    qDebug() << measureKits.measure(Department::Obstetrics::AbdominalCircumference, 18.34);
    // qDebug() << measureKits.measure(Department::Obstetrics::HeadCircumference, 16.26);
    // qDebug() << measureKits.measure(Department::Obstetrics::CrownRumpLength, 5.60);
    qDebug() << measureKits.measure(Department::FetalWeight::Hadlock1, 18.34, 5.24);
    qDebug() << measureKits.measure(Department::FetalWeight::Hadlock2, 18.34, 5.24, 7.52);
    ApplicationManager::instance()->init();
    QGuiApplication       app{argc, argv};
    QQmlApplicationEngine engine{};
    ViewManager::instance(engine)->init();
    // SpdLogger::instance()->init(QDir{QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)}.filePath("log/SonixLog_1.txt").toStdString());
    // spdlog::set_level(spdlog::level::trace);
    // SPDLOG_WARN("---=======2:{}", "String");
    // SPDLOG_ERROR("---=======3");
#if defined(Q_OS_ANDROID)
    QNativeInterface::QAndroidApplication::hideSplashScreen(0);
#endif
    return QGuiApplication::exec();
}
