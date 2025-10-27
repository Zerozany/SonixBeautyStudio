#include "AndroidWindow.h"

AndroidWindow::AndroidWindow(QQuickWindow* _parent) : QQuickWindow{_parent}
{
}

void AndroidWindow::exposeEvent(QExposeEvent* _ev)
{
    if (this->isExposed())
    {
        // qDebug() << "this->isExposed()";
        // Q_EMIT this->appDisplayChanged(true);
    }
    else
    {
        // qDebug() << "!!!!!this->isExposed()";
        // Q_EMIT this->appDisplayChanged(false);
    }
    QQuickWindow::exposeEvent(_ev);
}

void AndroidWindow::onAppDisplayChanged(bool _tag)
{
    if (_tag)
    {
        this->show();
    }
    else
    {
        this->hide();
    }
}
