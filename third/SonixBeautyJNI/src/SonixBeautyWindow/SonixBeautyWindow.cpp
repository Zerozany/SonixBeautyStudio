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
            QMetaObject::invokeMethod(window, "onCreate", Qt::QueuedConnection);
        }
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_NotifyStart(JNIEnv*, jclass)
    {
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            QMetaObject::invokeMethod(window, "onStart", Qt::QueuedConnection);
        }
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_NotifyStop(JNIEnv*, jclass)
    {
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            QMetaObject::invokeMethod(window, "onStop", Qt::QueuedConnection);
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
    Java_com_sonixbeauty_activity_AppActivity_NotifyPause(JNIEnv*, jclass)
    {
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            QMetaObject::invokeMethod(window, "onPause", Qt::QueuedConnection);
        }
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
    Java_com_sonixbeauty_activity_AppActivity_NotifyDestroy(JNIEnv*, jclass)
    {
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            QMetaObject::invokeMethod(window, "onDestroy", Qt::QueuedConnection);
        }
    }
}
#endif

static constexpr uint16_t INTERVAL{300};

SonixBeautyWindow::SonixBeautyWindow(QQuickWindow* _parent) : QQuickWindow{_parent}
{
    std::invoke(&SonixBeautyWindow::setSonixBeautyWindow, this);
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

auto SonixBeautyWindow::setSonixBeautyWindow() noexcept -> void
{
    if (m_instance == this)
    {
        return;
    }
    m_instance = this;
}

auto SonixBeautyWindow::setWindowPropertys() noexcept -> void
{
#if defined(Q_OS_ANDROID)
    this->setGraphicsApi(QSGRendererInterface::OpenGL);
    this->setVisibility(QWindow::AutomaticVisibility);
    this->setFlags(Qt::Window | Qt::ExpandedClientAreaHint);
#endif
}

auto SonixBeautyWindow::connectSignal2Slot() noexcept -> void
{
#if defined(Q_OS_ANDROID)

    connect(this, &SonixBeautyWindow::onCreate, this, &SonixBeautyWindow::onCreateChanged, Qt::QueuedConnection);

    connect(this, &SonixBeautyWindow::onStart, this, &SonixBeautyWindow::onStartChanged, Qt::QueuedConnection);

    connect(this, &SonixBeautyWindow::onStop, this, &SonixBeautyWindow::onStopChanged, Qt::QueuedConnection);

    connect(this, &SonixBeautyWindow::onRestart, this, &SonixBeautyWindow::onRestartChanged, Qt::QueuedConnection);

    connect(this, &SonixBeautyWindow::onPause, this, &SonixBeautyWindow::onPauseChanged, Qt::QueuedConnection);

    connect(this, &SonixBeautyWindow::onResume, this, &SonixBeautyWindow::onResumeChanged, Qt::QueuedConnection);

    connect(this, &SonixBeautyWindow::onDestroy, this, &SonixBeautyWindow::onDestroyChanged, Qt::QueuedConnection);

#endif
    connect(this, &SonixBeautyWindow::sceneGraphInitialized, this, [this] { qDebug() << "sceneGraphInitialized"; }, Qt::DirectConnection);

    connect(this, &SonixBeautyWindow::sceneGraphAboutToStop, this, [this] { qDebug() << "sceneGraphAboutToStop"; }, Qt::DirectConnection);

    connect(this, &SonixBeautyWindow::sceneGraphInvalidated, this, [this] { qDebug() << "sceneGraphInvalidated"; }, Qt::DirectConnection);
}

void SonixBeautyWindow::exposeEvent(QExposeEvent* _ev)
{
    QQuickWindow::exposeEvent(_ev);
}

void SonixBeautyWindow::onCreateChanged()
{
    qDebug() << "onCreateChanged";
}

void SonixBeautyWindow::onStartChanged()
{
    // qDebug() << "onStartChanged";
}

void SonixBeautyWindow::onStopChanged()
{
    // qDebug() << "onStopChanged";
}

void SonixBeautyWindow::onRestartChanged()
{
    qDebug() << "onRestartChanged";
    QTimer::singleShot(INTERVAL, [this] {
        QMetaObject::invokeMethod(this, "show", Qt::QueuedConnection);
    });
}

void SonixBeautyWindow::onPauseChanged()
{
    qDebug() << "onPauseChanged";
    QMetaObject::invokeMethod(this, "hide", Qt::QueuedConnection);
    // if (rendererInterface()->getResource(this, QSGRendererInterface::OpenGLContextResource))
}

void SonixBeautyWindow::onResumeChanged()
{
    // qDebug() << "onResumeChanged";
}

void SonixBeautyWindow::onDestroyChanged()
{
    // qDebug() << "onDestroyChanged";
}
