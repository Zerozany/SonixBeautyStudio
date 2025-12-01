_Pragma("once");
#include <QObject>
#include <string>
#include <map>

#if defined(Q_OS_WINDOWS) && defined(_MSC_VER)
    #ifdef SONIXBEAUTYSYSTEM
        #define SONIXEX_API Q_DECL_EXPORT
    #else
        #define SONIXEX_API Q_DECL_IMPORT
    #endif
#else
    #define SONIXEX_API
#endif

class SONIXEX_API WifiModuleBase : public QObject
{
    Q_OBJECT
public:
    explicit(true) WifiModuleBase(QObject* _parent = nullptr);
    virtual ~WifiModuleBase() noexcept = default;

private:
    virtual auto init() noexcept -> void = 0;

public:
    virtual auto searchWifiDevice() noexcept -> std::map<std::string, std::string> = 0;

    virtual auto curConnectedWifi() noexcept -> std::string = 0;

    virtual auto disconnectWifi() noexcept -> bool = 0;

    virtual auto connectWifi2Ssid(const std::string& _ssid, const std::string& _password) noexcept -> bool = 0;
};

inline WifiModuleBase::WifiModuleBase(QObject* _parent) : QObject{_parent}
{
}
