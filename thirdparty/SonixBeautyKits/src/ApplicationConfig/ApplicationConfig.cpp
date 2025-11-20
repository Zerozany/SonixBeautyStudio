#include "ApplicationConfig.h"
#include <QQuickStyle>
#include <QGuiApplication>

ApplicationConfig::ApplicationConfig(QObject* _parent) : QObject{_parent}
{
}

auto ApplicationConfig::instance() noexcept -> ApplicationConfig*
{
    static ApplicationConfig systemConfig{};
    return &systemConfig;
}

auto ApplicationConfig::init() noexcept -> void
{
    std::invoke(&ApplicationConfig::initAppEnv, this);
    std::invoke(&ApplicationConfig::initAppStyle, this);
    std::invoke(&ApplicationConfig::initAppAttribute, this);
}

auto ApplicationConfig::setAppEnv(const char* _envName, const QByteArray& _value) noexcept -> void
{
    qputenv(_envName, _value);
}

auto ApplicationConfig::setAppAttribute(const Qt::ApplicationAttribute _attribute, bool _switch) noexcept -> void
{
    QGuiApplication::setAttribute(_attribute, _switch);
}

auto ApplicationConfig::initAppEnv() noexcept -> void
{
#if defined(Q_OS_ANDROID)
    qputenv("QT_ANDROID_BACKGROUND_ACTIONS_QUEUE_SIZE", "50");
    qputenv("QT_OPENGL_DEBUG", "1");  // 启用 OpenGL 调试
#elif defined(Q_OS_WINDOWS)

#endif
    qputenv("QSG_RENDER_LOOP", "threaded");   // 使用独立的线程的渲染循环模式
    qputenv("QSG_RENDER_CONTINUOUSLY", "0");  // 禁用连续渲染，优化性能
}

auto ApplicationConfig::initAppStyle() noexcept -> void
{
#if defined(Q_OS_ANDROID)
    QQuickStyle::setStyle("Material");
#elif defined(Q_OS_WINDOWS)
    QQuickStyle::setStyle("Basic");
#endif
}

auto ApplicationConfig::initAppAttribute() noexcept -> void
{
#if defined(Q_OS_ANDROID)
    QGuiApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QGuiApplication::setAttribute(Qt::AA_CompressTabletEvents);
#elif defined(Q_OS_WINDOWS)

#endif
}
