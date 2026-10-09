#include "QmlDebug.h"
#include <QJSEngine>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include "DataServer.h"
#include "DataPacket.h"

QmlDebug* QmlDebug::create(QQmlEngine* _qmlEngine, QJSEngine* _qJSEngine)
{
    Q_UNUSED(_qJSEngine);
    static QmlDebug* qmlDebug{new QmlDebug{qobject_cast<QQmlApplicationEngine*>(_qmlEngine)}};
    return qmlDebug;
}

QmlDebug::QmlDebug(QObject* _parent) : QObject{_parent}
{
    QObject::connect(DataServer::instance(), &QTcpSocket::readyRead, [&]() {
        DataPacket dataPacket{};
        QByteArray recvData{DataServer::instance()->readAll()};
        if (!dataPacket.deserializationFrame(recvData))
        {
            return;
        }
        this->setRecvData(QDateTime::currentDateTime().toString("hh:mm:ss ").toUtf8() + recvData.toHex(' '));
    });
}

void QmlDebug::sendDatas()
{
    if (DataServer::instance()->state() != QAbstractSocket::ConnectedState)
    {
        return;
    }
    DataPacket dataPacket{};
    this->setSendData(QDateTime::currentDateTime().toString("hh:mm:ss ").toUtf8() + dataPacket.serializationFrame().toHex());
    DataServer::instance()->write(dataPacket.serializationFrame());
}
