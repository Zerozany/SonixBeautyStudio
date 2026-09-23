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
}

void TcpServer::onReadyRead()
{
}

void TcpServer::onBytesWritten(quint64 _bytes)
{
    Q_UNUSED(_bytes)
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
            break;
        case TcpServer::SocketError::HostNotFoundError:
            break;
        default:
            break;
    }
}

void TcpServer::onWifiConnectedSuccessful()
{
    this->connectToHost("192.168.0.10", 5061);
    if (!this->waitForConnected(3000))
    {
        qDebug() << "Tcp Connect failed:" << this->errorString();
    }
}
