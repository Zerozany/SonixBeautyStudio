#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ViewEngine.h"
#include "Translator.h"
// #include "ThemeManager.h"
// #include <QDebug>
// #include "SonixLogger.h"
// #include <QDir>
// #include <QStandardPaths>
#include "ApplicationConfig.h"

#if defined(Q_OS_ANDROID)
    #include <QJniObject>
    #include <QJniEnvironment>
// #include "AndroidContext.h"
// #include "AndroidWifModule.h"
#endif
// #include <QQuickStyle>

int main(int argc, char* argv[])
{
    // QQuickStyle::setStyle("Material");
    ApplicationConfig::instance()->init("Material");
    QGuiApplication app{argc, argv};
    // qDebug() << ThemeManager::create(nullptr, nullptr)->currentTheme();
    QQmlApplicationEngine engine{};
    // Translator::create(&engine, nullptr)->setLanguage(":/i18n/qml_zh_CN.qm");
    ViewEngine::instance()->init(&engine);
    // SonixLogger::init(QDir{QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)}.filePath("log/SonixLog_1.txt").toStdString());
    // SonixLogger::setLevel(spdlog::level::warn);
#if defined(Q_OS_ANDROID)
    // qDebug() << "-----: " << AndroidContext::instance()->context();
    // for (const auto& [k, v] : AndroidWifModule::instance()->searchWifiDevice().toStdMap())
    // {
    //     qDebug() << k << ":" << v;
    // }
    QNativeInterface::QAndroidApplication::hideSplashScreen(0);
#endif
    return QGuiApplication::exec();
}
