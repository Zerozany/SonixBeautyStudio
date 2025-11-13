#include "SonixBeautyWindow.h"
#include <QExposeEvent>
#include <QTimer>

#if defined(Q_OS_ANDROID)
#include <QJniObject>
#include <QJniEnvironment>

extern "C" {

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyCreate(JNIEnv*, jclass)
    {
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyStart(JNIEnv*, jclass)
    {
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyStop(JNIEnv*, jclass)
    {
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyPause(JNIEnv*, jclass)
    {
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            Q_EMIT window->onPause();
        }
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyRestart(JNIEnv*, jclass)
    {
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            Q_EMIT window->onRestart();
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

    connect(this, &SonixBeautyWindow::onRestart, this, &SonixBeautyWindow::onRestartChanged, Qt::QueuedConnection);

    connect(this, &SonixBeautyWindow::onPause, this, &SonixBeautyWindow::onPauseChanged, Qt::QueuedConnection);

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
    this->setSurfaceType(QWindow::OpenGLSurface);
    this->setVisibility(QWindow::FullScreen);
#endif
    this->setVisible(true);
}

void SonixBeautyWindow::exposeEvent(QExposeEvent* _ev)
{
    QQuickWindow::exposeEvent(_ev);
}

void SonixBeautyWindow::onPauseChanged()
{
    this->hide();
}

void SonixBeautyWindow::onRestartChanged()
{
    QTimer::singleShot(INTERVAL, [this] {
        if (this->isSceneGraphInitialized())
        {
            this->showFullScreen();
        }
    });
}
