#include "ApplicationManager.h"

#if defined(Q_OS_WINDOWS)
    #include "SingletonApplication.h"
#endif

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
#if defined(Q_OS_WINDOWS)
    SingletonApplication::instance()->init();
#endif
    std::invoke(&ApplicationManager::setSoftwareStyle, this, m_applicationStyle);
    // std::invoke(&SoftwareManager::setSoftwareAttribute, this);
    // std::invoke(&SoftwareManager::setSoftwareEnv, this);
}
