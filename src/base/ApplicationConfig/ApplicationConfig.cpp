#include "ApplicationConfig.h"

ApplicationConfig::ApplicationConfig(SoftwareManager* _parent) : SoftwareManager{_parent}
{
}

auto ApplicationConfig::instance() noexcept -> ApplicationConfig*
{
    static ApplicationConfig applicationConfig{};
    return &applicationConfig;
}

auto ApplicationConfig::init() noexcept -> void
{
    std::invoke(&ApplicationConfig::setSoftwareStyle, this, m_applicationStyle);
    // std::invoke(&SoftwareManager::setSoftwareAttribute, this);
    // std::invoke(&SoftwareManager::setSoftwareEnv, this);
}
