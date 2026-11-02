_Pragma("once");
#include "TcpSocket.h"
#include "DataStructure.hpp"

class DataSocket : public TcpSocket
{
    Q_OBJECT
public:
    static auto instance(QObject* _parent = nullptr) noexcept -> DataSocket*;

    ~DataSocket() noexcept override = default;

    Q_DISABLE_COPY_MOVE(DataSocket)

private:
    explicit(true) DataSocket(QObject* _parent = nullptr);

    auto connectSignal2Slot() noexcept -> void override;

private Q_SLOTS:
    void onReadyRead() override;

    void onBytesWritten(quint64 _bytes) override;

    void onConnected() override;

    void onDisconnected() override;

    void onErrorOccurred(const DataSocket::SocketError& _error) override;

public Q_SLOTS:
    void onWifiConnectSuccessful();
};
