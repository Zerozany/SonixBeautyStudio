#include "QmlDebug.h"
#include <QJSEngine>
#include <QQmlEngine>
#include <QQmlApplicationEngine>

#include <QDataStream>
#include <QIODevice>
#include "TcpServer.h"
#include "DataStructure.hpp"

static quint16 crc16_xmodem(const QByteArray& data)
{
    quint16 crc{0x0000};
    for (unsigned char b : data)
    {
        crc ^= (quint16)b << 8;
        for (int i = 0; i < 8; ++i)
        {
            crc = (crc & 0x8000) ? (crc << 1) ^ 0x1021 : (crc << 1);
        }
    }
    return crc;
}

static QByteArray buildWriteUdmFrame()
{
    // ---- 1. 填充 DataUDM ----
    DataStructure::DataUDM udmData{};

    // Product Area 头：0x02 0x0F
    udmData.productAreaHeader[0] = 0x02;
    udmData.productAreaHeader[1] = 0x0F;

    // ProductMFR = "hifu"
    std::memcpy(udmData.productMFR, "hifu", 4);

    // ProductName = "NERCUM"
    std::memcpy(udmData.productName, "NERCUM", 6);

    // ProductSN = "USL1H00000001"
    std::memcpy(udmData.productSN, "USL1H00000001", 13);

    // DeviceID 留空，固件自动补 MAC
    // DeviceSN、DeviceVersion 按需填

    // ---- 2. 把 DataUDM 序列化成 256 字节 ----
    QByteArray udm(256, '\0');
    std::memcpy(udm.data(), &udmData, sizeof(udmData));  // 前 130 字节
    // 130~255 保留，保持 0

    // ---- 3. 帧头 ----
    DataStructure::DataHeader hdr{};
    hdr.packetSIZE = 0x0045;  // 69 → 276 字节
    hdr.RW         = 0x0001;  // 写，不回包

    QByteArray header;
    {
        QDataStream ds(&header, QIODevice::WriteOnly);
        ds.setByteOrder(QDataStream::LittleEndian);
        ds.writeRawData(reinterpret_cast<const char*>(&hdr), sizeof(hdr));
    }

    // ---- 4. 帧尾 ----
    DataStructure::DataTail tail{};
    tail.packetClassCode = 0x06;
    tail.burstLength     = 0x40;  // 64 → 256 字节
    tail.addrByte0       = 0x80;  // 0xFFFFFF80
    tail.addrByte1       = 0xFF;
    tail.addrByte2       = 0xFF;
    tail.addrByte3       = 0xFF;

    QByteArray tailBytes;
    {
        QDataStream ds(&tailBytes, QIODevice::WriteOnly);
        ds.setByteOrder(QDataStream::LittleEndian);
        ds.writeRawData(reinterpret_cast<const char*>(&tail), sizeof(tail));
    }

    // ---- 5. CRC（覆盖 [0..11] + [14..15]） ----
    QByteArray crcArea = header + tailBytes.left(2);
    quint16    crc     = crc16_xmodem(crcArea);

    // ---- 6. 组装：12 头 + 2 CRC + 6 tail + 256 数据 = 276 字节 ----
    QByteArray frame;
    {
        QDataStream ds(&frame, QIODevice::WriteOnly);
        ds.setByteOrder(QDataStream::LittleEndian);
        ds.writeRawData(header.constData(), header.size());        // 12
        ds << crc;                                                 // 2
        ds.writeRawData(tailBytes.constData(), tailBytes.size());  // 6
        ds.writeRawData(udm.constData(), udm.size());              // 256
    }
    return frame;  // 276 字节
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
        // qDebug() << "readyRead, buf size =" << g_rxBuf.size();
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
            {
                break;  // 整帧没到齐，等下次
            }
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
            // ---- 帧头 12 字节 → DataHeader ----
            DataStructure::DataHeader hdr{};
            std::memcpy(&hdr, frame.constData(), sizeof(hdr));
            // ---- 偏移 14-19 → DataTail ----
            DataStructure::DataTail tail{};
            std::memcpy(&tail, frame.constData() + 14, sizeof(tail));
            // qDebug() << "RX: RW=" << hdr.RW;
            // qDebug() << "Class=" << tail.packetClassCode;
            // qDebug() << "Burst=" << tail.burstLength;
            // qDebug() << "hdr.packetType =" << hdr.packetType;
            // qDebug() << "hdr.packetC =" << hdr.packetC;
            // qDebug() << "hdr.packetT =" << hdr.packetT;
            // qDebug() << "hdr.packetCNT =" << hdr.packetCNT;
            // qDebug() << "hdr.packetSIZE =" << hdr.packetSIZE;
            // qDebug() << "hdr.streamID =" << hdr.streamID;
            // qDebug() << "hdr.frameEOF =" << hdr.frameEOF;
            // qDebug() << "hdr.lineEOF =" << hdr.lineEOF;
            // qDebug() << "hdr.cmdNUM =" << hdr.cmdNUM;
            // qDebug() << "hdr.PAD =" << hdr.PAD;
            // qDebug() << "hdr.OUI =" << hdr.OUI;
            // qDebug() << "hdr.RW =" << hdr.RW;
            // qDebug() << "tail.packetClassCode =" << tail.packetClassCode;
            // qDebug() << "tail.burstLength =" << tail.burstLength;
            // qDebug() << "tail.addrByte0 =" << tail.addrByte0;
            // qDebug() << "tail.addrByte1 =" << tail.addrByte1;
            // qDebug() << "tail.addrByte2 =" << tail.addrByte2;
            // qDebug() << "tail.addrByte3 =" << tail.addrByte3;
            quint32    addr = tail.addrByte0 | (tail.addrByte1 << 8) | (tail.addrByte2 << 16) | (tail.addrByte3 << 24);
            QByteArray udm  = frame.mid(20, tail.burstLength * 4);
            qDebug() << "Addr =" << QString::number(addr, 16);
            qDebug() << "UDM  =" << udm.toHex(' ');
            this->setRecvData(QDateTime::currentDateTime().toString("hh:mm:ss ").toUtf8() + udm.toHex(' '));

            DataStructure::DataUDM udmData{};
            std::memcpy(&udmData, udm.constData(), sizeof(udmData));  // 只拷前 130 字节
            auto bytesToQString = [](const std::uint8_t* data, int len) -> QString {
                int end = 0;
                while (end < len && data[end] != '\0') ++end;
                return QString::fromLatin1(reinterpret_cast<const char*>(data), end);
            };

            qDebug() << "ProductMFR  =" << bytesToQString(udmData.productMFR, 8);
            qDebug() << "ProductName =" << bytesToQString(udmData.productName, 8);
            qDebug() << "ProductSN   =" << bytesToQString(udmData.productSN, 16);
            qDebug() << "DeviceID    =" << bytesToQString(udmData.deviceID, 16);
            qDebug() << "DeviceSN    =" << bytesToQString(udmData.deviceSN, 32);
            qDebug() << "DeviceVer   =" << bytesToQString(udmData.deviceVersion, 40);
        }
    });
}

void QmlDebug::sendDatas()
{
    if (TcpServer::instance()->state() != QAbstractSocket::ConnectedState)  // 如果状态为未连接则直接跳过发送
    {
        return;
    }
    QByteArray frame{buildWriteUdmFrame()};
    this->setSendData(QDateTime::currentDateTime().toString("hh:mm:ss ").toUtf8() + frame.toHex());
    TcpServer::instance()->write(frame);
}
