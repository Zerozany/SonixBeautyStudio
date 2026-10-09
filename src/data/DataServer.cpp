#include "DataServer.h"

namespace Private
{
    static constexpr const char* DataHost{"192.168.0.10"};
    static constexpr quint16     DataPort{5061};
}  // namespace Private

auto DataServer::instance(QObject* _parent) noexcept -> DataServer*
{
    static DataServer* tcpServer{new DataServer{_parent}};
    return tcpServer;
}

DataServer::DataServer(QObject* _parent) : TcpSocket{_parent}
{
    std::invoke(&DataServer::connectSignal2Slot, this);
}

auto DataServer::connectSignal2Slot() noexcept -> void
{
}

void DataServer::onReadyRead()
{
}

void DataServer::onBytesWritten(quint64 _bytes)
{
    Q_UNUSED(_bytes)
}

void DataServer::onConnected()
{
    qDebug() << "Tcp onConnected";
}

void DataServer::onDisconnected()
{
    qDebug() << "Tcp onDisconnected";
}

void DataServer::onErrorOccurred(const DataServer::SocketError& _error)
{
    switch (_error)
    {
        case DataServer::SocketError::ConnectionRefusedError:
            break;
        case DataServer::SocketError::HostNotFoundError:
            break;
        default:
            break;
    }
}

void DataServer::onWifiConnectSuccessful()
{
    this->connectToHost(Private::DataHost, Private::DataPort);
    if (!this->waitForConnected(3000))
    {
        qDebug() << "Tcp Connect failed:" << this->errorString();
    }
}
