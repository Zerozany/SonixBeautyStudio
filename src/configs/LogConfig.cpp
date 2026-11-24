#include "LogConfig.h"

#include <QStandardPaths>
#include <QDir>
#include <QGuiApplication>

namespace Private
{
    static constexpr const char* LogConfigPath{":/config/settings/logConfig.ini"};
}  // namespace Private

LogConfig* LogConfig::instance(QObject* _parent) noexcept
{
    static LogConfig* logConfig{new LogConfig{Private::LogConfigPath, _parent}};
    return logConfig;
}

LogConfig::LogConfig(const QString& _fileName, QObject* _parent) : SettingsManager{_fileName, QSettings::IniFormat, _parent}
{
    SettingsManager::init();
}

QString LogConfig::logSavePath()
{
#if defined(Q_OS_WINDOWS)
    return QDir{QDir{QGuiApplication::applicationDirPath()}.filePath(this->m_logDirectory)}.filePath(this->m_logFile);
#elif defined(Q_OS_ANDROID)
    return QDir{QDir{QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)}.filePath(this->m_logDirectory)}.filePath(this->m_logFile);
#else
    return QDir{QDir{QGuiApplication::applicationDirPath()}.filePath(this->m_logDirectory)}.filePath(this->m_logFile);
#endif
    return QString{};
}
