#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ViewEngine.h"
// #include "Translator.h"
// #include "ThemeManager.h"
// #include <QDebug>
// #include "SonixLogger.h"
// #include <QDir>
// #include <QStandardPaths>
// #include "ApplicationConfig.h"

#if defined(Q_OS_ANDROID)
    #include <QJniObject>
    #include <QJniEnvironment>
// #include "AndroidWifiConfig.h"
#endif

int main(int argc, char* argv[])
{
    // ApplicationConfig::instance()->init();
    QGuiApplication app{argc, argv};
    // qDebug() << ThemeManager::create(nullptr, nullptr)->currentTheme();
    // Translator::create(nullptr, nullptr)->load(":/translate/SonixBeautyStudio_en.qm");
    QQmlApplicationEngine engine{};
    ViewEngine::instance()->init(&app, &engine);
    // SonixLogger::init(QDir{QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)}.filePath("log/SonixLog_1.txt").toStdString());
    // SonixLogger::setLevel(spdlog::level::warn);
#if defined(Q_OS_ANDROID)
    QNativeInterface::QAndroidApplication::hideSplashScreen(0);
#endif
    return QGuiApplication::exec();
}
