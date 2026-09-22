#include "TcpServer.h"

auto TcpServer::instance(QObject* _parent) noexcept -> TcpServer*
{
    static TcpServer* tcpServer{new TcpServer{_parent}};
    return tcpServer;
}

TcpServer::TcpServer(QObject* _parent) : TcpSocket{_parent}
{
}

auto TcpServer::onReadyRead() -> void
{
}

auto TcpServer::onBytesWritten(quint64 _bytes) -> void
{
}

auto TcpServer::onConnected() -> void
{
}

auto TcpServer::onDisconnected() -> void
{
}
