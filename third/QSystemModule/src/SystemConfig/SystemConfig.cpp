#include "SystemConfig.h"
#include <QQuickStyle>
#include <QGuiApplication>
#include <QDir>

SystemConfig::SystemConfig(QObject* _parent) : QObject{_parent}
{
    std::invoke(&SystemConfig::setAppEnv, this);
    std::invoke(&SystemConfig::setAppStyle, this);
    std::invoke(&SystemConfig::setAppAttribute, this);
}

auto SystemConfig::setAppEnv() noexcept -> void
{
    qputenv("QT_OPENGL_DEBUG", "1");          // 启用 OpenGL 调试
    qputenv("QSG_RENDER_LOOP", "threaded");   // 使用独立的线程的渲染循环模式
    qputenv("QSG_RENDER_CONTINUOUSLY", "0");  // 禁用连续渲染，优化性能
}

auto SystemConfig::setAppStyle() noexcept -> void
{
#if defined(Q_OS_ANDROID)
    QQuickStyle::setStyle("Material");
#else
    QQuickStyle::setStyle("Default");
#endif
}

auto SystemConfig::setAppAttribute() noexcept -> void
{
#if defined(Q_OS_ANDROID)
    QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);  // 使用 OpenGL ES 渲染
#elif defined(Q_OS_WINDOWS)
    QGuiApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);  // 强制使用软件 OpenGL 渲染（可能在某些平台上提高兼容性）
    QGuiApplication::setAttribute(Qt::AA_UseDesktopOpenGL);   // 使用桌面 OpenGL

#endif
    QGuiApplication::setAttribute(Qt::AA_CompressHighFrequencyEvents);  // 启用高频事件压缩，减少高频事件的处理，优化性能
    QGuiApplication::setAttribute(Qt::AA_QtQuickUseDefaultSizePolicy);  // 启用 Qt Quick 使用默认的大小策略
}
