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

    // private Q_SLOTS:
    auto onReadyRead() -> void override;

    auto onBytesWritten(quint64 _bytes) -> void override;

    auto onConnected() -> void override;

    auto onDisconnected() -> void override;
};
