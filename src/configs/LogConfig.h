_Pragma("once");
#include "SettingsManager.h"
#include "QuickMacro.hpp"

class LogConfig final : public SettingsManager
{
    Q_OBJECT
    QUICK_PROPERTY(QString, m_logDirectory, logDirectory, logDirectory, setLogDirectory, logDirectoryChanged)
    QUICK_PROPERTY(QString, m_logFile, logFile, logFile, setLogFile, logFileChanged)
    Q_CLASSINFO("logDirectory", "Path")
    Q_CLASSINFO("logFile", "Path")

public:
    static LogConfig* instance(QObject* _parent = nullptr) noexcept;

    ~LogConfig() noexcept override = default;

    Q_DISABLE_COPY_MOVE(LogConfig)

private:
    explicit(true) LogConfig(const QString& _fileName, QObject* _parent = nullptr);

public:
    QString logSavePath();

Q_SIGNALS:
    void logDirectoryChanged();
    void logFileChanged();

private:
    QString m_logDirectory{};
    QString m_logFile{};
};
