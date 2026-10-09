_Pragma("once");
#include <QByteArray>
#include "DataStructure.hpp"
#include "QuickMacro.hpp"

class DataPacket
{
public:
    explicit(true) DataPacket();

    ~DataPacket() noexcept = default;

public:
    auto serializationFrame() -> QByteArray;

    auto deserializationFrame(const QByteArray& _frame) -> bool;

public:
    DataStructure::DataHeader dataHeader{};
    DataStructure::DataTail   dataTail{};
    DataStructure::DataUDM    dataUDM{};
};
