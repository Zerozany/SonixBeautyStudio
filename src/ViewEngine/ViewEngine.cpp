#include "ViewEngine.h"
#include <QTimer>
#include <QQmlApplicationEngine>
#include <QGuiApplication>

#if defined(Q_OS_ANDROID)
#include "AndroidWindow.h"
#elif defined(Q_OS_WINDOWS)
#include "WinWindow.h"
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
    m_qmlApplicationEngine->addImportPath("qrc:/");
    m_qmlApplicationEngine->load(QUrl("qrc:/SonixBeautyStudio/view/Main.qml"));
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
    m_quickWindow->setPersistentSceneGraph(true);
    m_quickWindow->setPersistentGraphics(true);
}

auto ViewEngine::connectSignal2Slot() noexcept -> void
{
    connect(m_qmlApplicationEngine, &QQmlApplicationEngine::objectCreationFailed, m_guiApplication, [] { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
}
