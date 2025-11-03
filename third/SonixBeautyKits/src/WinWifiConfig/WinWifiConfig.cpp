#include "WinWifiConfig.h"
#include <print>
#include <span>

#if defined(_WIN32)
#include <windows.h>
#include <wlanapi.h>
#pragma comment(lib, "wlanapi.lib")

WinWifiConfig::WinWifiConfig(WifiConfigBase* _parent) : WifiConfigBase{_parent}
{
    std::invoke(&WinWifiConfig::init, this);
}

auto WinWifiConfig::init() noexcept -> void
{
    auto wlanCallback{[](PWLAN_NOTIFICATION_DATA _data, PVOID _context) -> void {
        WifiConfigBase* self{reinterpret_cast<WifiConfigBase*>(_context)};
        if (!self || _data->NotificationSource != WLAN_NOTIFICATION_SOURCE_ACM)
        {
            return;
        }
        switch (_data->NotificationCode)
        {
            case wlan_notification_acm_scan_complete:  // 表示一次 Wi-Fi 扫描完成
            {
                break;
            }
            case wlan_notification_acm_scan_fail:  // 扫描失败，可能是无线网卡问题、驱动错误或权限不足
            {
                break;
            }
            case wlan_notification_acm_connection_complete:  // 成功连接到 Wi-Fi，网络已建立
            {
                break;
            }
            case wlan_notification_acm_interface_arrival:  // WLAN 接口插入（热插拔）
            {
                break;
            }
            case wlan_notification_acm_interface_removal:  // WLAN 接口移除（热拔插）
            {
                break;
            }
            case wlan_notification_acm_connection_start:  // 开始尝试连接某个 Wi-Fi
            {
                [[fallthrough]];
            }
            case wlan_notification_acm_connection_attempt_fail:  // 连接尝试失败，例如密码错误、信号太弱、认证失败
            {
                [[fallthrough]];
            }
            case wlan_notification_acm_disconnecting:  // 正在断开 Wi-Fi（还没彻底断开）
            {
                [[fallthrough]];
            }
            case wlan_notification_acm_disconnected:  // 已经断开 Wi-Fi
            {
                break;
            }
            default:
            {
                break;
            }
        }
    }};

    DWORD version{};
    // 打开WLAN句柄
    if (DWORD dwResult{WlanOpenHandle(2, nullptr, &version, &m_hClient)}; dwResult != ERROR_SUCCESS)
    {
        std::println("WlanOpenHandle failed, error code: {}", dwResult);
        return;
    }
    if (DWORD dwResult{WlanRegisterNotification(m_hClient, WLAN_NOTIFICATION_SOURCE_ACM, TRUE, wlanCallback, this, nullptr, nullptr)};
        dwResult != ERROR_SUCCESS)
    {
        std::println("WlanRegisterNotification failed: {}", dwResult);
        return;
    }
}

auto WinWifiConfig::searchWifiDevice() noexcept -> std::map<std::string, std::string>
{
    PWLAN_INTERFACE_INFO_LIST          pIfList{nullptr};
    std::map<std::string, std::string> deviceMap{};
    if (DWORD dwResult{WlanEnumInterfaces(m_hClient, nullptr, &pIfList)}; dwResult != ERROR_SUCCESS)
    {
        return deviceMap;
    }
    // 遍历所有 WLAN 接口
    for (auto& iface : std::span{pIfList->InterfaceInfo, pIfList->dwNumberOfItems})
    {
        // 先触发扫描
        if (DWORD dwScan{WlanScan(m_hClient, &iface.InterfaceGuid, nullptr, nullptr, nullptr)};
            dwScan != ERROR_SUCCESS)
        {
            continue;
        }
        PWLAN_AVAILABLE_NETWORK_LIST pBssList{nullptr};
        if (DWORD res{WlanGetAvailableNetworkList(m_hClient, &iface.InterfaceGuid, 0, nullptr, &pBssList)}; res != ERROR_SUCCESS || !pBssList)
        {
            continue;
        }
        // 遍历当前接口的所有可用 Wi-Fi 网络
        for (auto& netWork : std::span{pBssList->Network, pBssList->dwNumberOfItems})
        {
            if (netWork.dot11Ssid.uSSIDLength == 0)
            {
                continue;
            }
            std::string ssid(reinterpret_cast<const char*>(netWork.dot11Ssid.ucSSID), netWork.dot11Ssid.uSSIDLength);
            std::string signalQualityObj{std::to_string(netWork.wlanSignalQuality)};
            deviceMap.emplace(ssid, signalQualityObj);
        }
        WlanFreeMemory(pBssList);
    }
    WlanFreeMemory(pIfList);
#if true
    if (!deviceMap.empty())
    {
        for (const auto& [k, v] : deviceMap)
        {
            std::println("SSID: {}, signalQuality: {}", k, v);
        }
    }
#endif
    return deviceMap;
}

auto WinWifiConfig::curConnectedWifi() noexcept -> std::string
{
    std::string curConnectedStr{};
    do
    {
        PWLAN_INTERFACE_INFO_LIST pIfList{nullptr};
        if (DWORD dwResult{WlanEnumInterfaces(m_hClient, nullptr, &pIfList)}; dwResult != ERROR_SUCCESS)
        {
            std::println("WlanEnumInterfaces failed with error: {}", dwResult);
            curConnectedStr = std::string{};
            break;
        }
        PWLAN_CONNECTION_ATTRIBUTES pConnectInfo{nullptr};
        DWORD                       connectInfoSize{sizeof(WLAN_CONNECTION_ATTRIBUTES)};
        WLAN_OPCODE_VALUE_TYPE      opCode{wlan_opcode_value_type_invalid};
        PWLAN_INTERFACE_INFO        pIfInfo{static_cast<WLAN_INTERFACE_INFO*>(&pIfList->InterfaceInfo[0])};
        if (pIfInfo->isState != wlan_interface_state_connected)
        {
            curConnectedStr = std::string{};
            WlanFreeMemory(pIfList);
            break;
        }
        DWORD dwResult{WlanQueryInterface(m_hClient, &pIfInfo->InterfaceGuid, wlan_intf_opcode_current_connection, nullptr,
                                          &connectInfoSize, reinterpret_cast<PVOID*>(&pConnectInfo), &opCode)};
        if (dwResult != ERROR_SUCCESS)
        {
            std::println("WlanQueryInterface failed with error: {}", dwResult);
            curConnectedStr = std::string{};
            WlanFreeMemory(pIfList);
            break;
        }
        if (pConnectInfo->isState != wlan_interface_state_connected)
        {
            curConnectedStr = std::string{};
            WlanFreeMemory(pIfList);
            break;
        }
        curConnectedStr.resize(std::wcstombs(nullptr, pConnectInfo->strProfileName, 0));
        std::wcstombs(curConnectedStr.data(), pConnectInfo->strProfileName, curConnectedStr.size());
        WlanFreeMemory(pIfList);
    } while (false);
    return curConnectedStr;
}

auto WinWifiConfig::disconnectWifi() noexcept -> bool
{
    PWLAN_INTERFACE_INFO_LIST pIfList{nullptr};
    if (DWORD dwResult{WlanEnumInterfaces(m_hClient, nullptr, &pIfList)}; dwResult != ERROR_SUCCESS)
    {
        std::println("WlanEnumInterfaces failed with error: {}", dwResult);
        return false;
    }
    PWLAN_INTERFACE_INFO pIfInfo{static_cast<WLAN_INTERFACE_INFO*>(&pIfList->InterfaceInfo[0])};
#if false
    // 查询当前连接的 Wi-Fi 配置名称
    PWLAN_CONNECTION_ATTRIBUTES pConnectInfo{nullptr};
    DWORD                       connectInfoSize{sizeof(WLAN_CONNECTION_ATTRIBUTES)};
    WLAN_OPCODE_VALUE_TYPE      opCode{};
    std::wstring                profileName{};
    if (WlanQueryInterface(m_hClient, &pIfInfo->InterfaceGuid, wlan_intf_opcode_current_connection, nullptr, &connectInfoSize, reinterpret_cast<PVOID*>(&pConnectInfo), &opCode) == ERROR_SUCCESS)
    {
        if (pConnectInfo->isState == wlan_interface_state_connected)
        {
            profileName = pConnectInfo->strProfileName;
        }
        WlanFreeMemory(pConnectInfo);
    }
#endif
    if (DWORD dwResult{WlanDisconnect(m_hClient, &pIfInfo->InterfaceGuid, nullptr)}; dwResult != ERROR_SUCCESS)
    {
        std::println("WlanDisconnect failed with error: {}", dwResult);
        WlanFreeMemory(pIfList);
        return false;
    }
#if false
    // 删除 Wi-Fi 配置文件
    if (!profileName.empty())
    {
        if (DWORD dwResult{WlanDeleteProfile(m_hClient, &pIfInfo->InterfaceGuid, profileName.c_str(), nullptr)}; dwResult != ERROR_SUCCESS)
        {
            std::println("WlanDeleteProfile failed for {}: {}", std::string(profileName.begin(), profileName.end()), dwResult);
        }
        else
        {
            std::println("Wi-Fi profile {} deleted successfully", std::string(profileName.begin(), profileName.end()));
        }
    }
#endif
    WlanFreeMemory(pIfList);
    return true;
}

auto WinWifiConfig::connectWifi2Ssid(const std::string& _ssid, const std::string& _password) noexcept -> bool
{
    static auto wifiProfileHead{[](const std::string& _ssid, const std::string& _password) -> std::wstring {
        std::string utf8Xml{std::format(
            R"(<?xml version="1.0"?>)"
            R"(<WLANProfile xmlns="http://www.microsoft.com/networking/WLAN/profile/v1">)"
            "<name>{}</name>"
            "<SSIDConfig>"
            "<SSID>"
            "<name>{}</name>"
            "</SSID>"
            "</SSIDConfig>"
            "<connectionType>ESS</connectionType>"
            "<connectionMode>auto</connectionMode>"
            "<autoSwitch>false</autoSwitch>"
            "<MSM>"
            "<security>"
            "<authEncryption>"
            "<authentication>WPA2PSK</authentication>"
            "<encryption>AES</encryption>"
            "<useOneX>false</useOneX>"
            "</authEncryption>"
            "<sharedKey>"
            "<keyType>passPhrase</keyType>"
            "<protected>false</protected>"
            "<keyMaterial>{}</keyMaterial>"
            "</sharedKey>"
            "</security>"
            "</MSM>"
            "</WLANProfile>",
            _ssid, _ssid, _password)};
        return std::wstring{utf8Xml.begin(), utf8Xml.end()};
    }};

    PWLAN_INTERFACE_INFO_LIST pIfList{nullptr};
    if (DWORD dwResult{WlanEnumInterfaces(m_hClient, nullptr, &pIfList)}; dwResult != ERROR_SUCCESS)
    {
        std::println("WlanEnumInterfaces failed with error: {}", dwResult);
        return false;
    }
    PWLAN_INTERFACE_INFO pIfInfo{static_cast<WLAN_INTERFACE_INFO*>(&pIfList->InterfaceInfo[0])};
    std::wstring         wStr{wifiProfileHead(_ssid, _password)};
    WLAN_REASON_CODE     wlanReason{};
    if (DWORD dwResult{WlanSetProfile(m_hClient, &pIfInfo->InterfaceGuid, 0, wStr.c_str(), nullptr, TRUE, nullptr, &wlanReason)}; dwResult != ERROR_SUCCESS)
    {
        std::println("WlanSetProfile failed with error: {}", dwResult);
        WlanFreeMemory(pIfList);
        return false;
    }
    std::wstring                                wStrProfileName{_ssid.begin(), _ssid.end()};
    std::unique_ptr<WLAN_CONNECTION_PARAMETERS> pConPara{std::make_unique<WLAN_CONNECTION_PARAMETERS>()};
    pConPara->wlanConnectionMode = wlan_connection_mode_profile;
    pConPara->strProfile         = wStrProfileName.c_str();
    pConPara->pDot11Ssid         = nullptr;
    pConPara->pDesiredBssidList  = nullptr;
    pConPara->dot11BssType       = dot11_BSS_type_infrastructure;
    pConPara->dwFlags            = WLAN_CONNECTION_HIDDEN_NETWORK;
    if (DWORD dwResult{WlanConnect(m_hClient, &pIfInfo->InterfaceGuid, pConPara.get(), nullptr)}; dwResult != ERROR_SUCCESS)
    {
        std::println("WlanConnect failed with error: {}", dwResult);
        WlanFreeMemory(pIfList);
        return false;
    }
    return true;
}
#endif
