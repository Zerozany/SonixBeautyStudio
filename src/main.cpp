#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "SystemConfig.h"
#include "ViewEngine.h"
// #include "AndroidWifiConfig.h"
// #include "Translator.h"
// #include "ThemeManager.h"
// #include <QDebug>

int main(int argc, char* argv[])
{
    SystemConfig::instance()->init();
    QGuiApplication app{argc, argv};
    // qDebug() << ThemeManager::create(nullptr, nullptr)->currentTheme();
    // Translator::create(nullptr, nullptr)->load(":/translate/SonixBeautyStudio_en.qm");
    QQmlApplicationEngine engine{};
    ViewEngine::instance()->init(&app, &engine);
    // SonixLogger::init(QDir{QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)}.filePath("log/SonixLog_1.txt").toStdString());
    // SonixLogger::setLevel(spdlog::level::warn);
    return QGuiApplication::exec();
}
