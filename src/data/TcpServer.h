_Pragma("once");
#include "TcpSocket.h"

class TcpServer : public TcpSocket
{
    Q_OBJECT
public:
    static auto instance(QObject* _parent = nullptr) noexcept -> TcpServer*;

    ~TcpServer() noexcept override = default;

    Q_DISABLE_COPY_MOVE(TcpServer)

private:
    explicit(true) TcpServer(QObject* _parent = nullptr);

    auto connectSignal2Slot() noexcept -> void override;

private Q_SLOTS:
    void onReadyRead() override;

    void onBytesWritten(quint64 _bytes) override;

    void onConnected() override;

    void onDisconnected() override;

    void onErrorOccurred(const TcpServer::SocketError& _error) override;

public Q_SLOTS:
    void onWifiConnectedSuccessful();
};
