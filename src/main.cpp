#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "SystemConfig.h"
#include "ViewEngine.h"

int main(int argc, char* argv[])
{
    SystemConfig::instance()->init();
    QGuiApplication       app{argc, argv};
    QQmlApplicationEngine engine{};
    ViewEngine::instance()->init(&app, &engine);
    // SonixLogger::init(QDir{QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)}.filePath("log/SonixLog_1.txt").toStdString());
    // SonixLogger::setLevel(spdlog::level::warn);
    return QGuiApplication::exec();
}
