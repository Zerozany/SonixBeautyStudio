#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "SystemConfig.h"
#include "ViewEngine.h"
// #include "Translator.h"
// #include "ThemeManager.h"
// #include <QDebug>

#if defined(Q_OS_ANDROID)
#include <QJniObject>
#include <QJniEnvironment>
// #include "AndroidWifiConfig.h"
#endif

int main(int argc, char* argv[])
{
    qputenv("QT_ANDROID_BACKGROUND_ACTIONS_QUEUE_SIZE", "50");
    qputenv("QT_LOGGING_RULES", "qt.qml.debug=true");
    // qputenv("QML_IMPORT_PATH", (QGuiApplication::applicationDirPath() + "/../thirdparty").toUtf8());
    SystemConfig::instance()->init();
    QGuiApplication app{argc, argv};
    // qDebug() << ThemeManager::create(nullptr, nullptr)->currentTheme();
    // Translator::create(nullptr, nullptr)->load(":/translate/SonixBeautyStudio_en.qm");
    QQmlApplicationEngine engine{};
    ViewEngine::instance()->init(&app, &engine);
    // SonixLogger::init(QDir{QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)}.filePath("log/SonixLog_1.txt").toStdString());
    // SonixLogger::setLevel(spdlog::level::warn);
#if defined(Q_OS_ANDROID)
    QNativeInterface::QAndroidApplication::hideSplashScreen(3000);
#endif
    return QGuiApplication::exec();
}
