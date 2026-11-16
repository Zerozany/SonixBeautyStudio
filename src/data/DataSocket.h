_Pragma("once");
#include <QTcpSocket>
#include "DataStructure.hpp"

class DataSocket : public QTcpSocket
{
    Q_OBJECT
public:
    static auto instance(QObject* _parent = nullptr) noexcept -> DataSocket*;

    ~DataSocket() noexcept override = default;

    Q_DISABLE_COPY_MOVE(DataSocket)

private:
    explicit(true) DataSocket(QObject* _parent = nullptr);

    auto connectSignal2Slot() noexcept -> void;

private Q_SLOTS:
    void onReadyRead();

    void onBytesWritten(quint64 _bytes);

    void onConnected();

    void onDisconnected();

    void onErrorOccurred(const DataSocket::SocketError& _error);

public Q_SLOTS:
    void onWifiConnectSuccessful();
};
