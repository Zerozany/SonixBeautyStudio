#include "DataSocket.h"

namespace Private
{
    static constexpr const char* DataHost{"192.168.0.10"};
    static constexpr quint16     DataPort{5061};
}  // namespace Private

auto DataSocket::instance(QObject* _parent) noexcept -> DataSocket*
{
    static DataSocket* tcpServer{new DataSocket{_parent}};
    return tcpServer;
}

DataSocket::DataSocket(QObject* _parent) : TcpSocket{_parent}
{
    std::invoke(&DataSocket::connectSignal2Slot, this);
}

auto DataSocket::connectSignal2Slot() noexcept -> void
{
}

void DataSocket::onReadyRead()
{
}

void DataSocket::onBytesWritten(quint64 _bytes)
{
    Q_UNUSED(_bytes)
}

void DataSocket::onConnected()
{
    qDebug() << "Tcp onConnected";
}

void DataSocket::onDisconnected()
{
    qDebug() << "Tcp onDisconnected";
}

void DataSocket::onErrorOccurred(const DataSocket::SocketError& _error)
{
    switch (_error)
    {
        case DataSocket::SocketError::ConnectionRefusedError:
            break;
        case DataSocket::SocketError::HostNotFoundError:
            break;
        default:
            break;
    }
}

void DataSocket::onWifiConnectSuccessful()
{
    this->connectToHost(Private::DataHost, Private::DataPort);
    if (!this->waitForConnected(3000))
    {
        qDebug() << "Tcp Connect failed:" << this->errorString();
    }
}
