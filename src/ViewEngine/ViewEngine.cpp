#include "ViewEngine.h"
#include <QTimer>
#include <QQmlApplicationEngine>
#include <QGuiApplication>

#if defined(Q_OS_ANDROID)
#include "SonixBeautyWindow.h"
#elif defined(Q_OS_WINDOWS)
#include "SonixBeautyWindow.h"
#endif

ViewEngine::ViewEngine(QObject* _parent) : QObject{_parent}
{
}

auto ViewEngine::instance() noexcept -> ViewEngine*
{
    static ViewEngine viewEngine{};
    return &viewEngine;
}

auto ViewEngine::init(QGuiApplication* _guiApplication, QQmlApplicationEngine* _qmlApplicationEngine) noexcept -> void
{
    std::invoke(&ViewEngine::initMember, _guiApplication, _qmlApplicationEngine);
    std::invoke(&ViewEngine::initEngine);
    std::invoke(&ViewEngine::initWindow);
    std::invoke(&ViewEngine::connectSignal2Slot);
}

auto ViewEngine::initMember(QGuiApplication* _guiApplication, QQmlApplicationEngine* _qmlApplicationEngine) noexcept -> void
{
    if (!_guiApplication)
    {
        return;
    }
    if (!_qmlApplicationEngine)
    {
        return;
    }
    m_guiApplication       = _guiApplication;
    m_qmlApplicationEngine = _qmlApplicationEngine;
}

auto ViewEngine::initEngine() noexcept -> void
{
    if (!m_qmlApplicationEngine)
    {
        return;
    }
#if defined(Q_OS_ANDROID)
    m_qmlApplicationEngine->loadFromModule("SonixBeautyStudio", "AndroidMain");
#elif defined(Q_OS_WINDOWS)
    m_qmlApplicationEngine->loadFromModule("SonixBeautyStudio", "WinMain");
#endif
}

auto ViewEngine::initWindow() noexcept -> void
{
    if (m_qmlApplicationEngine->rootObjects().isEmpty())
    {
        return;
    }
#if defined(Q_OS_ANDROID)
    m_quickWindow = qobject_cast<SonixBeautyWindow*>(m_qmlApplicationEngine->rootObjects().first());
#elif defined(Q_OS_WINDOWS)
    m_quickWindow = qobject_cast<SonixBeautyWindow*>(m_qmlApplicationEngine->rootObjects().first());
#endif
    if (!m_quickWindow)
    {
        return;
    }
}

auto ViewEngine::connectSignal2Slot() noexcept -> void
{
    connect(m_qmlApplicationEngine, &QQmlApplicationEngine::objectCreationFailed, m_guiApplication, [] { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
    connect(m_qmlApplicationEngine, &QQmlApplicationEngine::warnings, m_guiApplication, [](const QList<QQmlError>& warnings) {   for (const auto &warning : warnings) {
        qDebug() << warning.toString();
    } }, Qt::QueuedConnection);
}
