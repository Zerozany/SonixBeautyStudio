#include "ViewEngine.h"

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

ViewEngine::ViewEngine(QQmlApplicationEngine& _qmlApplicationEngine, ViewEngineBase* _parent) : ViewEngineBase{_qmlApplicationEngine, _parent}
{
}

auto ViewEngine::instance(QQmlApplicationEngine& _qmlApplicationEngine, ViewEngineBase* _parent) noexcept -> ViewEngine*
{
    static ViewEngine viewEngine{_qmlApplicationEngine, _parent};
    return &viewEngine;
}

auto ViewEngine::init() noexcept -> void
{
    std::invoke(&ViewEngine::engineLaod, this);
    std::invoke(&ViewEngine::connectSignal2Slot, this);
}

auto ViewEngine::engineLaod() noexcept -> void
{
    m_qmlApplicationEngine.loadFromModule("SonixBeautyStudio", "Main");
}

auto ViewEngine::connectSignal2Slot() noexcept -> void
{
}
