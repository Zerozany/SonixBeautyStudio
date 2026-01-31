#include "ApplicationConfig.h"

ApplicationConfig::ApplicationConfig(ApplicationConfigBase* _parent) : ApplicationConfigBase{_parent}
{
    std::invoke(&ApplicationConfig::init, this);
}

auto ApplicationConfig::instance() noexcept -> ApplicationConfig*
{
    static ApplicationConfig applicationConfig{};
    return &applicationConfig;
}

auto ApplicationConfig::init() noexcept -> void
{
    std::invoke(&ApplicationConfigBase::initAppStyle, this, m_applicationStyle);
    // std::invoke(&ApplicationConfigBase::initAppAttribute, this);
    // std::invoke(&ApplicationConfigBase::initAppEnv, this);
}
