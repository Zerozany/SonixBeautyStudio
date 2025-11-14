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
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyResume(JNIEnv*, jclass)
    {
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            Q_EMIT window->onResume();
        }
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

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyDestroy(JNIEnv*, jclass)
    {
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            Q_EMIT window->onDestroy();
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

    connect(this, &SonixBeautyWindow::onRestart, this, &SonixBeautyWindow::onRestartChanged, Qt::DirectConnection);

    connect(this, &SonixBeautyWindow::onResume, this, &SonixBeautyWindow::onResumeChanged, Qt::DirectConnection);

    connect(this, &SonixBeautyWindow::onPause, this, &SonixBeautyWindow::onPauseChanged, Qt::DirectConnection);

    connect(this, &SonixBeautyWindow::onDestroy, this, &SonixBeautyWindow::onDestroyChanged, Qt::DirectConnection);

#endif

    // connect(this, &QQuickWindow::beforeRendering, this, [this] { qDebug() << "beforeRendering"; }, Qt::DirectConnection);

    // connect(this, &QQuickWindow::afterRendering, this, [this] { qDebug() << "afterRendering"; }, Qt::DirectConnection);

    connect(this, &SonixBeautyWindow::sceneGraphInitialized, this, [this] { qDebug() << "sceneGraphInitialized"; }, Qt::DirectConnection);

    connect(this, &SonixBeautyWindow::sceneGraphAboutToStop, this, [this] { qDebug() << "sceneGraphAboutToStop"; }, Qt::DirectConnection);
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

#endif
    this->setVisibility(QWindow::FullScreen);
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

void SonixBeautyWindow::onResumeChanged()
{
}

void SonixBeautyWindow::onRestartChanged()
{
    QTimer::singleShot(INTERVAL, this, [this]() {
        this->showFullScreen();
    });
}

void SonixBeautyWindow::onStartChanged()
{
}

void SonixBeautyWindow::onDestroyChanged()
{
}
