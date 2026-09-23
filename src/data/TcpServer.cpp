#include "TcpServer.h"

auto TcpServer::instance(QObject* _parent) noexcept -> TcpServer*
{
    static TcpServer* tcpServer{new TcpServer{_parent}};
    return tcpServer;
}

TcpServer::TcpServer(QObject* _parent) : TcpSocket{_parent}
{
    std::invoke(&TcpServer::connectSignal2Slot, this);
}

auto TcpServer::connectSignal2Slot() noexcept -> void
{
    connect(this, &TcpServer::errorOccurred, this, &TcpServer::onErrorOccurred);
}

void TcpServer::onReadyRead()
{
}

void TcpServer::onBytesWritten(quint64 _bytes)
{
}

void TcpServer::onConnected()
{
    qDebug() << "Tcp onConnected";
}

void TcpServer::onDisconnected()
{
    qDebug() << "Tcp onDisconnected";
}

void TcpServer::onErrorOccurred(const TcpServer::SocketError& _error)
{
    switch (_error)
    {
        case TcpServer::SocketError::ConnectionRefusedError:
            /* code */
            break;
        case TcpServer::SocketError::HostNotFoundError:
            /* code */
            break;
        default:
            break;
    }
}
