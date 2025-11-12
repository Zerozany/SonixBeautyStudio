_Pragma("once");
#include <QObject>

#if defined(Q_OS_WINDOWS) && defined(_MSC_VER)
#ifdef SONIXEXPROTS
#define SONIXEX_API Q_DECL_EXPORT
#else
#define SONIXEX_API Q_DECL_IMPORT
#endif
#else
#define SONIXEX_API
#endif

class QJniObject;

class SONIXEX_API AndroidWifiConfig : public QObject
{
    Q_OBJECT
public:
    enum class WifiState
    {
        DISCONNECTED = 0,
        CONNECTSUCCESS,
        CONNECTERROR
    };

public:
    ~AndroidWifiConfig() noexcept = default;

    static auto instance() noexcept -> AndroidWifiConfig*;

private:
    explicit(true) AndroidWifiConfig(QObject* _parent = nullptr);

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
