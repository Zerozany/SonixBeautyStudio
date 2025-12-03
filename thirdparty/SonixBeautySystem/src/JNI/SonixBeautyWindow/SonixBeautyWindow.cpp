#include "SonixBeautyWindow.h"

#if defined(Q_OS_ANDROID)
    #include <QJniObject>
    #include <QJniEnvironment>
#endif

#if defined(Q_OS_ANDROID)
extern "C" {

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_core_MainActivity_QActivityVisibileChanged(JNIEnv*, jclass, jboolean _activityVisibile)
    {
        if (auto window{SonixBeautyWindow::instance()}; window)
        {
            QMetaObject::invokeMethod(window, "activityVisibileChanged", Qt::QueuedConnection, Q_ARG(bool, static_cast<bool>(_activityVisibile)));
        }
    }
}
#endif

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

void SonixBeautyWindow::onActivityVisibileChanged(bool _activityVisibile)
{
    if (_activityVisibile)
    {
        this->setVisible(true);
    }
    else
    {
        this->setVisible(false);
    }
}

auto SonixBeautyWindow::setWindowPropertys() noexcept -> void
{
#if defined(Q_OS_ANDROID)
    this->setGraphicsApi(QSGRendererInterface::OpenGL);
    this->setFlags(Qt::Window | Qt::ExpandedClientAreaHint);
    this->setVisibility(QWindow::FullScreen);
#endif
}

auto SonixBeautyWindow::connectSignal2Slot() noexcept -> void
{
#if defined(Q_OS_ANDROID)

    connect(this, &SonixBeautyWindow::activityVisibileChanged, this, &SonixBeautyWindow::onActivityVisibileChanged, Qt::QueuedConnection);

#endif
}
