#include "ViewEngine.h"
#include <QQmlApplicationEngine>
#include <QGuiApplication>

#if defined(Q_OS_ANDROID)
    #include "AndroidWindow.h"
#elif defined(Q_OS_WINDOWS)
    #include "WinWindow.h"
#endif

#if defined(Q_OS_ANDROID)
extern "C" {

    JNIEXPORT void JNICALL
    Java_com_zerosystem_core_MainActivity_QActivityVisibileChanged(JNIEnv*, jclass, jboolean _activityVisibile)
    {
        if (auto window{AndroidWindow::instance()}; window)
        {
            QMetaObject::invokeMethod(window, "activityVisibileChanged", Qt::QueuedConnection, Q_ARG(bool, static_cast<bool>(_activityVisibile)));
        }
    }
}
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
    std::invoke(&ViewEngine::initObject, _guiApplication, _qmlApplicationEngine);
    std::invoke(&ViewEngine::engineSetting);
    std::invoke(&ViewEngine::windowSetting);
    std::invoke(&ViewEngine::connectSignal2Slot);
}

auto ViewEngine::initObject(QGuiApplication* _guiApplication, QQmlApplicationEngine* _qmlApplicationEngine) noexcept -> void
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

auto ViewEngine::engineSetting() noexcept -> void
{
    if (!m_qmlApplicationEngine)
    {
        return;
    }
    m_qmlApplicationEngine->loadFromModule("SonixBeautyStudio", "Main");
}

auto ViewEngine::windowSetting() noexcept -> void
{
    if (m_qmlApplicationEngine->rootObjects().isEmpty())
    {
        return;
    }
#if defined(Q_OS_ANDROID)
    m_quickWindow = qobject_cast<AndroidWindow*>(m_qmlApplicationEngine->rootObjects().first());
#elif defined(Q_OS_WINDOWS)
    m_quickWindow = qobject_cast<WinWindow*>(m_qmlApplicationEngine->rootObjects().first());
#endif
    if (!m_quickWindow)
    {
        return;
    }
}

auto ViewEngine::connectSignal2Slot() noexcept -> void
{
    connect(m_qmlApplicationEngine, &QQmlApplicationEngine::objectCreationFailed, m_guiApplication, [] { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
    connect(m_qmlApplicationEngine, &QQmlApplicationEngine::warnings, m_guiApplication, [](const QList<QQmlError>& _warnings) {   for (const auto &warning : _warnings) {
        qDebug() << warning.toString();
    } }, Qt::QueuedConnection);
}
