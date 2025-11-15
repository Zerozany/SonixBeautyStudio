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
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_NotifyResume(JNIEnv*, jclass)
    {
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            QMetaObject::invokeMethod(window, "onResume", Qt::QueuedConnection);
        }
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_NotifyStop(JNIEnv*, jclass)
    {
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_NotifyPause(JNIEnv*, jclass)
    {
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            QMetaObject::invokeMethod(window, "onPause", Qt::QueuedConnection);
        }
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_NotifyRestart(JNIEnv*, jclass)
    {
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            QMetaObject::invokeMethod(window, "onRestart", Qt::QueuedConnection);
        }
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_NotifyDestroy(JNIEnv*, jclass)
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

    connect(this, &SonixBeautyWindow::onRestart, this, &SonixBeautyWindow::onRestartChanged, Qt::QueuedConnection);

    connect(this, &SonixBeautyWindow::onResume, this, &SonixBeautyWindow::onResumeChanged, Qt::QueuedConnection);

    connect(this, &SonixBeautyWindow::onPause, this, &SonixBeautyWindow::onPauseChanged, Qt::QueuedConnection);

    connect(this, &SonixBeautyWindow::onDestroy, this, &SonixBeautyWindow::onDestroyChanged, Qt::QueuedConnection);

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
    this->setVisibility(QWindow::FullScreen);
    this->setPersistentGraphics(false);
    this->setPersistentSceneGraph(false);
#endif
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
