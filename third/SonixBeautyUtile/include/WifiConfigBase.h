_Pragma("once");
#include <QObject>
#include <string>
#include <map>

class WifiConfigBase : public QObject
{
    Q_OBJECT
public:
    explicit(true) WifiConfigBase(QObject* _parent = nullptr);
    ~WifiConfigBase() noexcept = default;

private:
    virtual auto init() noexcept -> void = 0;

public:
    virtual auto searchWifiDevice() noexcept -> std::map<std::string, std::string> = 0;

    virtual auto curConnectedWifi() noexcept -> std::string = 0;

    virtual auto disconnectWifi() noexcept -> bool = 0;

    virtual auto connectWifi2Ssid(const std::string& _ssid, const std::string& _password) noexcept -> bool = 0;
};

inline WifiConfigBase::WifiConfigBase(QObject* _parent) : QObject{_parent}
{
}
