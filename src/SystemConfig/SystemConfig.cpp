#include "SystemConfig.h"
#include <QQuickStyle>
#include <QGuiApplication>
#include <QDir>

SystemConfig::SystemConfig(QObject* _parent) : QObject{_parent}
{
}

auto SystemConfig::instance() noexcept -> SystemConfig*
{
    static SystemConfig systemConfig{};
    return &systemConfig;
}

auto SystemConfig::init() noexcept -> void
{
    std::invoke(&SystemConfig::setAppEnv, this);
    std::invoke(&SystemConfig::setAppStyle, this);
    std::invoke(&SystemConfig::setAppAttribute, this);
}

auto SystemConfig::setAppEnv() noexcept -> void
{
#if defined(Q_OS_ANDROID)
    qputenv("QT_ANDROID_BACKGROUND_ACTIONS_QUEUE_SIZE", "50");
#elif defined(Q_OS_WINDOWS)

#endif
    qputenv("QT_OPENGL_DEBUG", "1");          // 启用 OpenGL 调试
    qputenv("QSG_RENDER_LOOP", "threaded");   // 使用独立的线程的渲染循环模式
    qputenv("QSG_RENDER_CONTINUOUSLY", "0");  // 禁用连续渲染，优化性能
}

auto SystemConfig::setAppStyle() noexcept -> void
{
#if defined(Q_OS_ANDROID)
    QQuickStyle::setStyle("Material");
#elif defined(Q_OS_WINDOWS)
    QQuickStyle::setStyle("Default");
#endif
}

auto SystemConfig::setAppAttribute() noexcept -> void
{
#if defined(Q_OS_ANDROID)
    QGuiApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QGuiApplication::setAttribute(Qt::AA_CompressTabletEvents);
#elif defined(Q_OS_WINDOWS)

#endif
}
