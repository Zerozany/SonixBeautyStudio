_Pragma("once");
#include "TcpSocket.h"
#include "DataStructure.hpp"

class DataServer : public TcpSocket
{
    Q_OBJECT
public:
    static auto instance(QObject* _parent = nullptr) noexcept -> DataServer*;

    ~DataServer() noexcept override = default;

    Q_DISABLE_COPY_MOVE(DataServer)

private:
    explicit(true) DataServer(QObject* _parent = nullptr);

    auto connectSignal2Slot() noexcept -> void override;

private Q_SLOTS:
    void onReadyRead() override;

    void onBytesWritten(quint64 _bytes) override;

    void onConnected() override;

    void onDisconnected() override;

    void onErrorOccurred(const DataServer::SocketError& _error) override;

public Q_SLOTS:
    void onWifiConnectSuccessful();
};
