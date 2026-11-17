#include "ApplicationManager.h"

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
    // std::invoke(&SoftwareManager::setSoftwareAttribute, this);
    // std::invoke(&SoftwareManager::setSoftwareEnv, this);
}
