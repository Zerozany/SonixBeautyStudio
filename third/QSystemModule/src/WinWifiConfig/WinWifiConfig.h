_Pragma("once");
#include "WifiConfigBase.h"

class WinWifiConfig : public WifiConfigBase
{
    using HANDLE = void*;

public:
    explicit(true) WinWifiConfig(WifiConfigBase* _parent = nullptr);
    ~WinWifiConfig() noexcept = default;

private:
    auto init() noexcept -> void override;

public:
    auto searchWifiDevice() noexcept -> std::map<std::string, std::string> override;

    auto curConnectedWifi() noexcept -> std::string override;

    auto disconnectWifi() noexcept -> bool override;

    auto connectWifi2Ssid(const std::string& _ssid, const std::string& _password) noexcept -> bool override;

private:
    HANDLE m_hClient{nullptr};
};
