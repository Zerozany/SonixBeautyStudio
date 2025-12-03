#include "SonixBeautyWindow.h"

SonixBeautyWindow::SonixBeautyWindow(QQuickWindow* _parent) : QQuickWindow{_parent}
{
    std::invoke(&SonixBeautyWindow::setWindowPropertys, this);
    std::invoke(&SonixBeautyWindow::connectSignal2Slot, this);
}

auto SonixBeautyWindow::connectSignal2Slot() noexcept -> void
{
}

auto SonixBeautyWindow::setWindowPropertys() noexcept -> void
{
#if defined(Q_OS_WINDOWS)
    this->setVisibility(QWindow::Maximized);
#endif
}
