#include "SonixBeautyWindow.h"
#include <QExposeEvent>

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
#if defined(Q_OS_WINDOWS)
    this->setVisibility(QWindow::Maximized);
#endif
}

void SonixBeautyWindow::exposeEvent(QExposeEvent* _ev)
{
    QQuickWindow::exposeEvent(_ev);
}
