_Pragma("once");
#include <QObject>
#if defined(Q_OS_ANDROID)
    #include "AndroidJNIManager.h"
#else
class AndroidJNIManager : public QObject
{
    Q_OBJECT
public:
    explicit(true) AndroidJNIManager(QObject* _parent = nullptr) : QObject{_parent} {};
};
#endif

class AndroidWifiManager final : public AndroidJNIManager
{
    Q_OBJECT
public:
    static auto instance(QObject* _parent = nullptr) noexcept -> AndroidWifiManager*;

    ~AndroidWifiManager() noexcept = default;

    Q_DISABLE_COPY_MOVE(AndroidWifiManager)

public:
    void connectToWifi(const QString& _ssid, const QString& _password);

    void disconnectWifi();

    QString currentWifiName();

    int currentWifiSignalQuality();

    QMap<QString, quint8> getWifiList();

private:
    explicit(true) AndroidWifiManager(QObject* _parent = nullptr);

    auto init() noexcept -> void;

Q_SIGNALS:
    void wifiConnectedSuccessful();

    void wifiConnectedFailed();

    void wifiLost();
};
