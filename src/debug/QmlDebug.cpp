#include "QmlDebug.h"
#include <QJSEngine>
#include <QQmlEngine>
#include <QQmlApplicationEngine>

#include <QDataStream>
#include <QIODevice>
#include "TcpServer.h"

static quint16 crc16_xmodem(const QByteArray& data)
{
    quint16 crc = 0x0000;
    for (unsigned char b : data)
    {
        crc ^= (quint16)b << 8;
        for (int i = 0; i < 8; ++i)
            crc = (crc & 0x8000) ? (crc << 1) ^ 0x1021 : (crc << 1);
    }
    return crc;
}

static QByteArray buildReadUdmFrame()
{
    // ---- 1. 先构建除 CRC 字段外的头部区域（前 12 字节） ----
    QByteArray header;
    {
        QDataStream ds(&header, QIODevice::WriteOnly);
        ds.setByteOrder(QDataStream::LittleEndian);  // 全部小端

        ds << quint16(0x0004);  // packetType=4, packetC/T=0, packetCNT=0
        ds << quint16(0x0005);  // packetSIZE=5 -> 20 字节
        ds << quint16(0x0000);  // StreamID
        ds << quint16(0x0001);  // FrameEOF=1, CmdNUM=0
        ds << quint16(0x0000);  // PAD/OUI
        ds << quint16(0x0001);  // RW=1 读
    }

    // ---- 2. 尾部数据（14 字节之后） ----
    QByteArray tail;
    {
        QDataStream ds(&tail, QIODevice::WriteOnly);
        ds.setByteOrder(QDataStream::LittleEndian);

        ds << quint16(0x0406);  // PacketClassCode=6, BurstLength=64
        ds << quint8(0x80);     // 地址 0xFFFFFF80 (小端)
        ds << quint8(0xFF);
        ds << quint8(0xFF);
        ds << quint8(0xFF);
    }

    // ---- 3. 计算 CRC（覆盖 header + tail 中的 2 字节） ----
    // 原逻辑: crcArea = f.left(12) + f.mid(14, 2)
    // f.mid(14,2) 就是 tail 的前 2 字节 (0x0406)
    QByteArray crcArea = header + tail.left(2);
    quint16    crc     = crc16_xmodem(crcArea);

    // ---- 4. 组装最终帧 ----
    QByteArray frame;
    {
        QDataStream ds(&frame, QIODevice::WriteOnly);
        ds.setByteOrder(QDataStream::LittleEndian);

        ds.writeRawData(header.constData(), header.size());  // 0..11
        ds << crc;                                           // 12..13 (小端)
        ds.writeRawData(tail.constData(), tail.size());      // 14..19
    }

    return frame;  // 20 字节
}

QmlDebug* QmlDebug::create(QQmlEngine* _qmlEngine, QJSEngine* _qJSEngine)
{
    Q_UNUSED(_qJSEngine);
    static QmlDebug* qmlDebug{new QmlDebug{qobject_cast<QQmlApplicationEngine*>(_qmlEngine)}};
    return qmlDebug;
}

QmlDebug::QmlDebug(QObject* _parent) : QObject{_parent}
{
    static QByteArray g_rxBuf{};

    QObject::connect(TcpServer::instance(), &QTcpSocket::readyRead, [&]() {
        g_rxBuf += TcpServer::instance()->readAll();
        qDebug() << "readyRead, buf size =" << g_rxBuf.size();
        while (g_rxBuf.size() >= 16)
        {
            // packetSIZE 表示整包占多少个 32bit word
            quint16 sizeRaw = (quint8)g_rxBuf[2] | ((quint8)g_rxBuf[3] << 8);
            int     total   = sizeRaw * 4;
            if (total < 20)
            {
                qDebug() << "包长度异常:" << total;
                break;
            }
            if (g_rxBuf.size() < total)
                break;  // 整帧没到齐，等下次

            QByteArray frame = g_rxBuf.left(total);
            g_rxBuf.remove(0, total);

            // CRC 校验（覆盖 [0..11] + [14..15]）
            QByteArray crcArea = frame.left(12) + frame.mid(14, 2);
            quint16    calc    = crc16_xmodem(crcArea);
            quint16    recv    = (quint8)frame[12] | ((quint8)frame[13] << 8);
            if (calc != recv)
            {
                qDebug() << "CRC 错误，丢弃整包";
                continue;
            }

            quint16 classBl   = (quint8)frame[14] | ((quint8)frame[15] << 8);
            quint16 burst     = classBl >> 4;
            quint8  classCode = classBl & 0x0F;
            quint16 rw        = (quint8)frame[10] | ((quint8)frame[11] << 8);

            qDebug() << "RX: RW=" << rw << " Class=" << classCode << " Burst=" << burst;

            quint32    addr = (quint8)frame[16] | ((quint8)frame[17] << 8) | ((quint8)frame[18] << 16) | ((quint8)frame[19] << 24);
            QByteArray udm  = frame.mid(20, burst * 4);  // 头部固定 20 字节

            qDebug() << "Addr =" << QString::number(addr, 16);
            qDebug() << "UDM  =" << udm.toHex(' ');
            this->setRecvData(QDateTime::currentDateTime().toString("hh:mm:ss ").toUtf8() + udm.toHex(' '));

            auto field = [&](int off, int len) -> QString {
                QByteArray raw = udm.mid(off, len);
                int        end = raw.indexOf('\0');
                if (end >= 0) raw.truncate(end);
                return QString::fromLatin1(raw);
            };
            QByteArray rawId = udm.mid(42, 16);
            qDebug() << "DeviceID raw hex:" << rawId.toHex(' ');
            qDebug() << "DeviceID raw ascii:" << QString::fromLatin1(rawId);
            qDebug() << "DeviceID field():" << field(42, 16);
            qDebug() << "ProductMFR  =" << field(10, 8);
            qDebug() << "ProductName =" << field(18, 8);
            qDebug() << "ProductSN   =" << field(26, 16);
            qDebug() << "DeviceID    =" << field(42, 16);
            qDebug() << "DeviceSN    =" << field(58, 32);
            qDebug() << "DeviceVer   =" << field(90, 40);
        }
    });
}

void QmlDebug::sendDatas()
{
    if (TcpServer::instance()->state() != QAbstractSocket::ConnectedState)
    {
        return;
    }
    QByteArray frame{buildReadUdmFrame()};
    this->setSendData(QDateTime::currentDateTime().toString("hh:mm:ss ").toUtf8() + frame.toHex());
    TcpServer::instance()->write(frame);
}
