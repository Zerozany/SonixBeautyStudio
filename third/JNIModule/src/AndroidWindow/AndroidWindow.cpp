#include "AndroidWindow.h"
#include <QExposeEvent>
#include <QTimer>

#if defined(Q_OS_ANDROID)
#include <QJniObject>
#include <QJniEnvironment>
#include "AndroidWindow.h"

extern "C" {

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyCreate(JNIEnv*, jclass)
    {
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyStart(JNIEnv*, jclass)
    {
        if (auto window{AndroidWindow::instance()}; window)
        {
            Q_EMIT window->onStart();
        }
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyStop(JNIEnv*, jclass)
    {
        if (auto window{AndroidWindow::instance()}; window)
        {
            Q_EMIT window->onStop();
        }
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyRestart(JNIEnv*, jclass)
    {
        if (auto window{AndroidWindow::instance()}; window)
        {
            Q_EMIT window->onRestart();
        }
    }
}
#endif

static constexpr uint16_t INTERVAL{300};

AndroidWindow::AndroidWindow(QQuickWindow* _parent) : QQuickWindow{_parent}
{
    m_instance = this;
    std::invoke(&AndroidWindow::connectSignal2Slot, this);
}

AndroidWindow::~AndroidWindow() noexcept
{
    if (m_instance == this)
    {
        m_instance = nullptr;
    }
}

auto AndroidWindow::instance() noexcept -> AndroidWindow*
{
    return m_instance;
}

auto AndroidWindow::connectSignal2Slot() noexcept -> void
{
    connect(this, &AndroidWindow::onStart, this, &AndroidWindow::onStartChanged, Qt::QueuedConnection);

    connect(this, &AndroidWindow::onStop, this, &AndroidWindow::onStopChanged, Qt::QueuedConnection);

    connect(this, &AndroidWindow::onRestart, this, &AndroidWindow::onRestartChanged, Qt::QueuedConnection);
}

void AndroidWindow::exposeEvent(QExposeEvent* _ev)
{
    QQuickWindow::exposeEvent(_ev);
}

void AndroidWindow::onStartChanged()
{
    QTimer::singleShot(INTERVAL, [this] {
        if (this->isSceneGraphInitialized())
        {
            this->show();
        }
    });
}

void AndroidWindow::onStopChanged()
{
    this->hide();
}

void AndroidWindow::onRestartChanged()
{
    QTimer::singleShot(INTERVAL, [this] {
        if (this->isSceneGraphInitialized())
        {
            this->show();
        }
    });
}
