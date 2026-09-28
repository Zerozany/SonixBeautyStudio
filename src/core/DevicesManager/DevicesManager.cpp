#include "DevicesManager.h"
#include <QJSEngine>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include "ProbeDevice.h"
#include "TcpServer.h"

#if defined(Q_OS_WINDOWS)
    #include "WinWlanManager.h"
#elif defined(Q_OS_ANDROID)
    #include "AndroidWifiManager.h"
#endif

namespace Private
{
#if defined(Q_OS_WINDOWS)
    using WifiManager = WinWlanManager;
#elif defined(Q_OS_ANDROID)
    using WifiManager = AndroidWifiManager;
#endif
}  // namespace Private

DevicesManager* DevicesManager::create(QQmlEngine* _qmlEngine, QJSEngine* _qJSEngine)
{
    Q_UNUSED(_qJSEngine);
    static DevicesManager* deviceList{new DevicesManager{qobject_cast<QQmlApplicationEngine*>(_qmlEngine)}};
    return deviceList;
}

DevicesManager::DevicesManager(QObject* _parent) : QObject{_parent}
{
    std::invoke(&DevicesManager::connectSignal2Slot, this);
}

void DevicesManager::connectSignal2Slot() noexcept
{
    connect(Private::WifiManager::instance(), &Private::WifiManager::wifiConnectSuccessful, TcpServer::instance(), &TcpServer::onWifiConnectSuccessful);
    connect(Private::WifiManager::instance(), &Private::WifiManager::wifiLost, TcpServer::instance(), &TcpServer::abort);
    connect(Private::WifiManager::instance(), &Private::WifiManager::wifiConnectFailed, [] {
        qDebug() << "wifiConnectedFailed";
    });
}

void DevicesManager::connectToWifi(const QString& _ssid, const QString& _password)
{
    Private::WifiManager::instance()->connectToWifi(_ssid, _password);
}

void DevicesManager::disconnectWifi()
{
    Private::WifiManager::instance()->disconnectWifi();
}

QString DevicesManager::currentWifiName()
{
    return Private::WifiManager::instance()->currentWifiName();
}

int DevicesManager::currentWifiSignalQuality()
{
    return Private::WifiManager::instance()->currentWifiSignalQuality();
}

void DevicesManager::refreshDevicesList()
{
    QVariantList          wifiListTmp{};
    QMap<QString, quint8> result{Private::WifiManager::instance()->getWifiList()};
    for (const auto& [_ssid, _level] : result.toStdMap())
    {
        wifiListTmp.append(QVariantMap{{QStringLiteral("ssid"), _ssid}, {QStringLiteral("level"), _level}});
    }
    // if (wifiListTmp.isEmpty())
    // {
    //     return;
    // }
    this->setDevicesList(wifiListTmp);
}
