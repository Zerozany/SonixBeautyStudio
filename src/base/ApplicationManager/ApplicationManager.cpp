#include "ApplicationManager.h"
#include "LogManager.h"

#include <QStandardPaths>
#include <QDir>
#include <QGuiApplication>

namespace Private
{
    static constexpr const char* LogDirName{"log"};
    static constexpr const char* LogFileName{"SonixLog.txt"};
}  // namespace Private

ApplicationManager::ApplicationManager(SoftwareManager* _parent) : SoftwareManager{_parent}
{
}

auto ApplicationManager::instance() noexcept -> ApplicationManager*
{
    static ApplicationManager applicationConfig{};
    return &applicationConfig;
}

auto ApplicationManager::init() noexcept -> void
{
    std::invoke(&ApplicationManager::setSoftwareStyle, this, m_applicationStyle);
    std::invoke(&ApplicationManager::thirdConfig, this);
    // std::invoke(&SoftwareManager::setSoftwareAttribute, this);
    // std::invoke(&SoftwareManager::setSoftwareEnv, this);
}

auto ApplicationManager::thirdConfig() noexcept -> void
{
#if defined(Q_OS_WINDOWS)
    LogManager::instance()->init(QDir{QDir{QGuiApplication::applicationDirPath()}.filePath(Private::LogDirName)}.filePath(Private::LogFileName).toStdString());
#elif defined(Q_OS_ANDROID)
    LogManager::instance()->init(QDir{QDir{QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)}.filePath(Private::LogDirName)}.filePath(Private::LogFileName).toStdString());
#else
    LogManager::instance()->init(QDir{QDir{QGuiApplication::applicationDirPath()}.filePath(Private::LogDirName)}.filePath(Private::LogFileName).toStdString());
#endif
    LogManager::instance()->set_level(spdlog::level::trace);
}
