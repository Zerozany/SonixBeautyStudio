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
// #include "AndroidContext.h"
// #include "AndroidWifModule.h"
#endif
// #include <QQuickStyle>
// #include "ThemeManager.h"

int main(int argc, char* argv[])
{
    SingletonApplication::instance()->init();
    // QQuickStyle::setStyle("Material");
    ApplicationConfig::instance()->init();
    QGuiApplication app{argc, argv};
    // qDebug() << ThemeManager::create(nullptr, nullptr)->currentTheme();
    QQmlApplicationEngine engine{};
    // Translator::create(&engine, nullptr)->setLanguage(":/i18n/qml_zh_CN.qm");
    ViewEngine::instance(engine)->init();
    // ZeroLogger::init(QDir{QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)}.filePath("log/SonixLog_1.txt").toStdString());
    // ZeroLogger::setLevel(spdlog::level::warn);
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
