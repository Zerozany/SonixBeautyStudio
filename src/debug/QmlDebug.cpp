#include "QmlDebug.h"
#include <QJSEngine>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include "DataSocket.h"
#include "DataPacket.h"

QmlDebug* QmlDebug::create(QQmlEngine* _qmlEngine, QJSEngine* _qJSEngine)
{
    Q_UNUSED(_qJSEngine);
    static QmlDebug* qmlDebug{new QmlDebug{qobject_cast<QQmlApplicationEngine*>(_qmlEngine)}};
    return qmlDebug;
}

QmlDebug::QmlDebug(QObject* _parent) : QObject{_parent}
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

void QmlDebug::sendDatas()
{
    if (DataSocket::instance()->state() != QAbstractSocket::ConnectedState)
    {
        return;
    }
    DataPacket dataPacket{};
    this->setSendData(QDateTime::currentDateTime().toString("hh:mm:ss ").toUtf8() + dataPacket.serializationFrame().toHex());
    DataSocket::instance()->write(dataPacket.serializationFrame());
}
