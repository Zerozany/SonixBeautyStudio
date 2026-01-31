#include "ApplicationConfig.h"
#include <QQuickStyle>
#include <QGuiApplication>

auto ApplicationConfig::instance() noexcept -> ApplicationConfig*
{
    static ApplicationConfig systemConfig{};
    return &systemConfig;
}

auto ApplicationConfig::init() noexcept -> void
{
    std::invoke(&ApplicationConfig::initAppStyle, this);
    std::invoke(&ApplicationConfig::initAppAttribute, this);
    std::invoke(&ApplicationConfig::initAppEnv, this);
}

ApplicationConfig::ApplicationConfig(QObject* _parent) : QObject{_parent}
{
}

auto ApplicationConfig::initAppStyle() noexcept -> void
{
#if defined(Q_OS_ANDROID)
    QQuickStyle::setStyle("Material");
#elif defined(Q_OS_WINDOWS)
    QQuickStyle::setStyle("Material");
#endif
}

auto ApplicationConfig::initAppAttribute() noexcept -> void
{
    // for (const auto& _attribute : _attributeVector)
    // {
    //     QGuiApplication::setAttribute(_attribute);
    // }
}

auto ApplicationConfig::initAppEnv() noexcept -> void
{
    // for (const auto& [_key, _value] : _envVariantMap.toStdMap())
    // {
    //     qputenv(_key.toUtf8(), _value.toByteArray().constData());
    // }
}
