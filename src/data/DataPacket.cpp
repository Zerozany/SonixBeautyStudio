#include "DataPacket.h"
#include <QDataStream>
#include <QIODevice>
#include <QDebug>

namespace Private
{
    static quint16 crc16_xmodem(const QByteArray& _data)
    {
        quint16 crc{0x0000};
        for (unsigned char b : _data)
        {
            crc ^= (quint16)b << 8;
            for (int i = 0; i < 8; ++i)
            {
                crc = (crc & 0x8000) ? (crc << 1) ^ 0x1021 : (crc << 1);
            }
        }
        return crc;
    }

    static QString bytesToQString(const std::uint8_t* _data, int _len)
    {
        int end{};
        while (end < _len && _data[end] != '\0')
        {
            ++end;
        };
        return QString::fromLatin1(reinterpret_cast<const char*>(_data), end);
    }
}  // namespace Private

DataPacket::DataPacket()
{
}

auto DataPacket::serializationFrame() const -> QByteArray
{
    QByteArray headerByte{};
    {
        QDataStream dataStream{&headerByte, QIODevice::WriteOnly};
        dataStream.setByteOrder(QDataStream::LittleEndian);
        dataStream.writeRawData(reinterpret_cast<const char*>(&this->dataHeader), sizeof(this->dataHeader));
    }
    QByteArray tailByte{};
    {
        QDataStream dataStream{&tailByte, QIODevice::WriteOnly};
        dataStream.setByteOrder(QDataStream::LittleEndian);
        dataStream.writeRawData(reinterpret_cast<const char*>(&this->dataTail), sizeof(this->dataTail));
    }
    QByteArray udmByte{};
    {
        QDataStream dataStream{&udmByte, QIODevice::WriteOnly};
        dataStream.setByteOrder(QDataStream::LittleEndian);
        dataStream.writeRawData(reinterpret_cast<const char*>(&this->dataUDM), sizeof(this->dataUDM));
    }
    QByteArray frame{};
    {
        QDataStream dataStream{&frame, QIODevice::WriteOnly};
        dataStream.setByteOrder(QDataStream::LittleEndian);
        dataStream.writeRawData(headerByte.constData(), headerByte.size());
        dataStream << Private::crc16_xmodem(headerByte + tailByte.left(2));
        dataStream.writeRawData(tailByte.constData(), tailByte.size());
        dataStream.writeRawData(udmByte.constData(), udmByte.size());
    }
    return frame;
}

auto DataPacket::deserializationFrame(const QByteArray& _frame) -> bool
{
    int total{(static_cast<uint8_t>(_frame[2]) | static_cast<uint8_t>(_frame[3] << 8)) * 4};
    if (total < 20 || _frame.size() < total)
    {
        return false;
    }
    QByteArray _deserializationFrame{_frame.left(total)};
    uint16_t   calc{Private::crc16_xmodem(_deserializationFrame.left(12) + _deserializationFrame.mid(14, 2))};
    uint16_t   recvCalc{static_cast<uint16_t>(static_cast<uint8_t>(_frame[12]) | (static_cast<uint8_t>(_frame[13]) << 8))};
    if (calc != recvCalc)
    {
        return false;
    }
    std::memcpy(&this->dataHeader, _deserializationFrame.constData(), sizeof(this->dataHeader));
    std::memcpy(&this->dataTail, _deserializationFrame.constData() + 14, sizeof(this->dataTail));
    std::memcpy(&this->dataUDM, _deserializationFrame.mid(20, this->dataTail.burstLength * 4), sizeof(this->dataUDM));
#if true
    qDebug() << "_frame.size=" << _frame.size();
    qDebug() << "RX: RW=" << this->dataHeader.RW;
    qDebug() << "Class=" << this->dataTail.packetClassCode;
    qDebug() << "Burst=" << this->dataTail.burstLength;
    qDebug() << "this->dataHeader.packetType =" << this->dataHeader.packetType;
    qDebug() << "this->dataHeader.packetC =" << this->dataHeader.packetC;
    qDebug() << "this->dataHeader.packetT =" << this->dataHeader.packetT;
    qDebug() << "this->dataHeader.packetCNT =" << this->dataHeader.packetCNT;
    qDebug() << "this->dataHeader.packetSIZE =" << this->dataHeader.packetSIZE;
    qDebug() << "this->dataHeader.streamID =" << this->dataHeader.streamID;
    qDebug() << "this->dataHeader.frameEOF =" << this->dataHeader.frameEOF;
    qDebug() << "this->dataHeader.lineEOF =" << this->dataHeader.lineEOF;
    qDebug() << "this->dataHeader.cmdNUM =" << this->dataHeader.cmdNUM;
    qDebug() << "this->dataHeader.PAD =" << this->dataHeader.PAD;
    qDebug() << "this->dataHeader.OUI =" << this->dataHeader.OUI;
    qDebug() << "this->dataHeader.RW =" << this->dataHeader.RW;
    qDebug() << "this->dataTail.packetClassCode =" << this->dataTail.packetClassCode;
    qDebug() << "this->dataTail.burstLength =" << this->dataTail.burstLength;
    qDebug() << "this->dataTail.addrByte0 =" << this->dataTail.addrByte0;
    qDebug() << "this->dataTail.addrByte1 =" << this->dataTail.addrByte1;
    qDebug() << "this->dataTail.addrByte2 =" << this->dataTail.addrByte2;
    qDebug() << "this->dataTail.addrByte3 =" << this->dataTail.addrByte3;
    qDebug() << "ProductMFR  =" << Private::bytesToQString(this->dataUDM.productMFR, 8);
    qDebug() << "ProductName =" << Private::bytesToQString(this->dataUDM.productName, 8);
    qDebug() << "ProductSN   =" << Private::bytesToQString(this->dataUDM.productSN, 16);
    qDebug() << "DeviceID    =" << Private::bytesToQString(this->dataUDM.deviceID, 16);
    qDebug() << "DeviceSN    =" << Private::bytesToQString(this->dataUDM.deviceSN, 32);
    qDebug() << "DeviceVer   =" << Private::bytesToQString(this->dataUDM.deviceVersion, 40);
#endif
    return true;
}
