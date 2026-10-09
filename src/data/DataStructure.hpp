_Pragma("once");
#include <cstdint>

namespace DataStructure
{
    struct DataHeader
    {
        std::uint16_t packetType : 4 {4};  // 第 3~0 位
        std::uint16_t packetC : 1 {0};     // 第 4 位
        std::uint16_t packetT : 1 {0};     // 第 5 位
        std::uint16_t packetCNT : 10 {0};  // 第 15~6 位
        std::uint16_t packetSIZE{0x0005};
        std::uint16_t streamID{0x0000};
        std::uint16_t frameEOF : 1 {0x01};
        std::uint16_t lineEOF : 1 {0x00};
        std::uint16_t cmdNUM : 14 {0x00};
        std::uint16_t PAD : 2 {0x00};
        std::uint16_t OUI : 14 {0x00};
        std::uint16_t RW{0x0001};
    };

    struct DataTail
    {
        std::uint16_t packetClassCode : 4 {0x06};  // 低 4 位
        std::uint16_t burstLength : 12 {0x40};     // 高 12 位
        std::uint8_t  addrByte0{0x80};
        std::uint8_t  addrByte1{0xFF};
        std::uint8_t  addrByte2{0xFF};
        std::uint8_t  addrByte3{0xFF};
    };

    struct DataUDM
    {
        std::uint8_t commonHeader[8]{};       // 偏移 0，8 字节
        std::uint8_t productAreaHeader[2]{};  // 偏移 8，2 字节
        std::uint8_t productMFR[8]{};         // 偏移 10，8 字节
        std::uint8_t productName[8]{};        // 偏移 18，8 字节
        std::uint8_t productSN[16]{};         // 偏移 26，16 字节
        std::uint8_t deviceID[16]{};          // 偏移 42，16 字节
        std::uint8_t deviceSN[32]{};          // 偏移 58，32 字节
        std::uint8_t deviceVersion[40]{};     // 偏移 90，40 字节
        std::uint8_t reserved[126]{};
    };

    static_assert(sizeof(DataStructure::DataUDM) == 256, "DataUDM must be 256 bytes");

}  // namespace DataStructure
