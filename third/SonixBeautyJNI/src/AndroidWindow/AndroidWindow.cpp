#include "AndroidWindow.h"
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
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            Q_EMIT window->onStart();
        }
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyStop(JNIEnv*, jclass)
    {
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            Q_EMIT window->onStop();
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

    connect(this, &SonixBeautyWindow::onStart, this, &SonixBeautyWindow::onStartChanged, Qt::QueuedConnection);

    connect(this, &SonixBeautyWindow::onStop, this, &SonixBeautyWindow::onStopChanged, Qt::QueuedConnection);

    connect(this, &SonixBeautyWindow::onRestart, this, &SonixBeautyWindow::onRestartChanged, Qt::QueuedConnection);
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
    this->setVisible(true);
#if defined(Q_OS_ANDROID)
    this->setVisibility(QWindow::AutomaticVisibility);
#elif defined(Q_OS_WINDOWS)
    this->setVisibility(QWindow::Windowed);
#endif
}

void SonixBeautyWindow::exposeEvent(QExposeEvent* _ev)
{
    QQuickWindow::exposeEvent(_ev);
}

void SonixBeautyWindow::onStartChanged()
{
    QTimer::singleShot(INTERVAL, [this] {
        if (this->isSceneGraphInitialized())
        {
            this->show();
        }
    });
}

void SonixBeautyWindow::onStopChanged()
{
    this->hide();
}

void SonixBeautyWindow::onRestartChanged()
{
    QTimer::singleShot(INTERVAL, [this] {
        if (this->isSceneGraphInitialized())
        {
            this->show();
        }
    });
}
