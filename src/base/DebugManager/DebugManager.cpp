#include "DebugManager.h"
#include <QJSEngine>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include "DataSocket.h"
#include "DataPacket.h"

DebugManager* DebugManager::create(QQmlEngine* _qmlEngine, QJSEngine* _qJSEngine)
{
    Q_UNUSED(_qJSEngine);
    static DebugManager* qmlDebug{new DebugManager{qobject_cast<QQmlApplicationEngine*>(_qmlEngine)}};
    return qmlDebug;
}

DebugManager::DebugManager(QObject* _parent) : QObject{_parent}
{
    QObject::connect(DataSocket::instance(), &QTcpSocket::readyRead, [&]() {
        DataPacket dataPacket{};
        QByteArray recvData{DataSocket::instance()->readAll()};
        if (!dataPacket.deserializationFrame(recvData))
        {
            return;
        }
        this->setRecvData(QDateTime::currentDateTime().toString("hh:mm:ss ").toUtf8() + recvData.toHex(' '));
    });
}

void DebugManager::sendDatas()
{
    if (DataSocket::instance()->state() != QAbstractSocket::ConnectedState)
    {
        return;
    }
    DataPacket dataPacket{};
    this->setSendData(QDateTime::currentDateTime().toString("hh:mm:ss ").toUtf8() + dataPacket.serializationFrame().toHex());
    DataSocket::instance()->write(dataPacket.serializationFrame());
}
