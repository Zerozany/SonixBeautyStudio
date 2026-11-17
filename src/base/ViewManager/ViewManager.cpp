#include "ViewManager.h"

#if defined(Q_OS_ANDROID)
    #include "AndroidWindow.h"
#elif defined(Q_OS_WINDOWS)
    #include "WinWindow.h"
#endif

#if defined(Q_OS_ANDROID)
extern "C" {

    JNIEXPORT void JNICALL Java_com_sonixbeauty_core_MainActivity_QActivityVisibileChanged(JNIEnv*, jclass, jboolean _activityVisibile)
    {
        if (auto window{AndroidWindow::instance()}; window)
        {
            QMetaObject::invokeMethod(window, "activityVisibileChanged", Qt::QueuedConnection, Q_ARG(bool, static_cast<bool>(_activityVisibile)));
        }
    }
}
#endif

ViewManager::ViewManager(QQmlApplicationEngine& _qmlApplicationEngine, ViewEngineManager* _parent) : ViewEngineManager{_qmlApplicationEngine, _parent}
{
}

auto ViewManager::instance(QQmlApplicationEngine& _qmlApplicationEngine, ViewEngineManager* _parent) noexcept -> ViewManager*
{
    static ViewManager viewEngine{_qmlApplicationEngine, _parent};
    return &viewEngine;
}

auto ViewManager::init() noexcept -> void
{
    std::invoke(&ViewManager::connectSignal2Slot, this);
    std::invoke(&ViewManager::loadModule, this);
}

auto ViewManager::loadModule() noexcept -> void
{
    m_qmlApplicationEngine.loadFromModule("SonixBeautyStudio", "Main");
}

auto ViewManager::connectSignal2Slot() noexcept -> void
{
}
