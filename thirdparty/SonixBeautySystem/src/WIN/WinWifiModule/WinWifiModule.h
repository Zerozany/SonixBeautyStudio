_Pragma("once");
#include "WifiModuleBase.h"

#if defined(Q_OS_WINDOWS) && defined(_MSC_VER)
    #ifdef SONIXBEAUTYSYSTEM
        #define SONIXEX_API Q_DECL_EXPORT
    #else
        #define SONIXEX_API Q_DECL_IMPORT
    #endif
#else
    #define SONIXEX_API
#endif

class SONIXEX_API WinWifiModule : public WifiModuleBase
{
    using HANDLE = void*;
    Q_OBJECT
public:
    explicit(true) WinWifiModule(WifiModuleBase* _parent = nullptr);
    ~WinWifiModule() noexcept = default;

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
