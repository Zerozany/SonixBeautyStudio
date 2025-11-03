#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "SystemConfig.h"
#include "ViewEngine.h"
// #include "Translator.h"

int main(int argc, char* argv[])
{
    SystemConfig::instance()->init();
    QGuiApplication app{argc, argv};
    // Translator::instance().load(":/translate/SonixBeautyStudio_en.qm");
    QQmlApplicationEngine engine{};
    ViewEngine::instance()->init(&app, &engine);
    // SonixLogger::init(QDir{QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)}.filePath("log/SonixLog_1.txt").toStdString());
    // SonixLogger::setLevel(spdlog::level::warn);
    return QGuiApplication::exec();
}
