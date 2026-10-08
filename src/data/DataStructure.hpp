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
        std::uint8_t  placeHolder_1{0x80};
        std::uint8_t  placeHolder_2{0xFF};
        std::uint8_t  placeHolder_3{0xFF};
        std::uint8_t  placeHolder_4{0xFF};
    };
}  // namespace DataStructure
