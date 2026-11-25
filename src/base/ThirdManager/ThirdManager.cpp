#include "ThirdManager.h"

#include "LogManager.h"
#include "LogConfig.h"

auto ThirdManager::instance(QObject* _parent) noexcept -> ThirdManager*
{
    static ThirdManager* thirdManager{new ThirdManager{_parent}};
    return thirdManager;
}

ThirdManager::ThirdManager(QObject* _parent) : QObject{_parent}
{
}

auto ThirdManager::init() noexcept -> void
{
    /// @brief LOG Init
    LogManager::instance()->init(LogConfig::instance()->logSavePath().toStdString());
#if defined(QT_DEBUG)
    LogManager::instance()->set_level(spdlog::level::debug);
#else
    LogManager::instance()->set_level(spdlog::level::warn);
#endif
}
