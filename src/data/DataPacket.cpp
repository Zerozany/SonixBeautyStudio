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
}  // namespace Private

DataPacket::DataPacket()
{
}

auto DataPacket::serializationFrame() -> QByteArray
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
    qDebug() << "_frame.size: " << _frame.size();

    // return false;
}
