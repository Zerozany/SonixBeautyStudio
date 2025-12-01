_Pragma("once");
#include <QObject>

class QJniObject;

class AndroidWifModule : public QObject
{
    Q_OBJECT
public:
    enum class WifiState : uint8_t
    {
        DISCONNECTED = 0,
        CONNECTSUCCESS,
        CONNECTERROR
    };

public:
    ~AndroidWifModule() noexcept = default;

    static auto instance() noexcept -> AndroidWifModule*;

private:
    explicit(true) AndroidWifModule(QObject* _parent = nullptr);

    auto init() noexcept -> void;

public:
    auto searchWifiDevice() noexcept -> QMap<QString, quint8>;

    auto curConnectedWifi() noexcept -> QString;

    auto connectWifi2Ssid(const QString& _ssid, const QString& _password) noexcept -> void;

Q_SIGNALS:
    void wifiStateChanged(WifiState _tag);

private:
    QJniObject* m_wifiObject{nullptr};
};
