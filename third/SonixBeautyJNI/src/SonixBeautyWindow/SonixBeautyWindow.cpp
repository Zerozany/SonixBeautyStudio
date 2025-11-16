#include "SonixBeautyWindow.h"
#include <QExposeEvent>
#include <QTimer>

#if defined(Q_OS_ANDROID)
#include <QJniObject>
#include <QJniEnvironment>

extern "C" {

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_NotifyCreate(JNIEnv*, jclass)
    {
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            QMetaObject::invokeMethod(window, "onCreate", Qt::DirectConnection);
        }
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_NotifyResume(JNIEnv*, jclass)
    {
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            QMetaObject::invokeMethod(window, "onResume", Qt::DirectConnection);
        }
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_NotifyStop(JNIEnv*, jclass)
    {
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            QMetaObject::invokeMethod(window, "onStop", Qt::DirectConnection);
        }
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_NotifyPause(JNIEnv*, jclass)
    {
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            QMetaObject::invokeMethod(window, "onPause", Qt::DirectConnection);
        }
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_NotifyRestart(JNIEnv*, jclass)
    {
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            QMetaObject::invokeMethod(window, "onRestart", Qt::DirectConnection);
        }
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_NotifyDestroy(JNIEnv*, jclass)
    {
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            QMetaObject::invokeMethod(window, "onDestroy", Qt::DirectConnection);
        }
    }
}
#endif

static constexpr uint16_t INTERVAL{300};

SonixBeautyWindow::SonixBeautyWindow(QQuickWindow* _parent) : QQuickWindow{_parent}
{
    std::invoke(&SonixBeautyWindow::setSonixBeautyWindow, this, this);
    std::invoke(&SonixBeautyWindow::connectSignal2Slot, this);
    std::invoke(&SonixBeautyWindow::setWindowPropertys, this);
}

SonixBeautyWindow::~SonixBeautyWindow() noexcept
{
    if (m_instance == this)
    {
        m_instance = nullptr;
    }
}

auto SonixBeautyWindow::instance() noexcept -> SonixBeautyWindow*
{
    return m_instance;
}
auto SonixBeautyWindow::connectSignal2Slot() noexcept -> void
{
#if defined(Q_OS_ANDROID)

    connect(this, &SonixBeautyWindow::onCreate, this, &SonixBeautyWindow::onCreateChanged, Qt::QueuedConnection);

    connect(this, &SonixBeautyWindow::onRestart, this, &SonixBeautyWindow::onRestartChanged, Qt::QueuedConnection);

    connect(this, &SonixBeautyWindow::onResume, this, &SonixBeautyWindow::onResumeChanged, Qt::QueuedConnection);

    connect(this, &SonixBeautyWindow::onPause, this, &SonixBeautyWindow::onPauseChanged, Qt::QueuedConnection);

    connect(this, &SonixBeautyWindow::onDestroy, this, &SonixBeautyWindow::onDestroyChanged, Qt::QueuedConnection);

#endif
}

auto SonixBeautyWindow::setSonixBeautyWindow(SonixBeautyWindow* _sonixBeautyWindow) noexcept -> void
{
    if (m_instance == _sonixBeautyWindow)
    {
        return;
    }
    m_instance = _sonixBeautyWindow;
}

auto SonixBeautyWindow::setWindowPropertys() noexcept -> void
{
#if defined(Q_OS_ANDROID)
    this->setVisibility(QWindow::AutomaticVisibility);
    this->setFlags(Qt::Window | Qt::MaximizeUsingFullscreenGeometryHint);
    this->setPersistentSceneGraph(true);
#endif
}
void SonixBeautyWindow::exposeEvent(QExposeEvent* _ev)
{
    QQuickWindow::exposeEvent(_ev);
}

void SonixBeautyWindow::onCreateChanged()
{
}

void SonixBeautyWindow::onPauseChanged()
{
    this->hide();
    this->setPersistentSceneGraph(false);
}

void SonixBeautyWindow::onResumeChanged()
{
}

void SonixBeautyWindow::onRestartChanged()
{
    QTimer::singleShot(INTERVAL, [this]() {
        this->setPersistentSceneGraph(true);
        this->show();
    });
}

void SonixBeautyWindow::onStartChanged()
{
}

void SonixBeautyWindow::onDestroyChanged()
{
}
