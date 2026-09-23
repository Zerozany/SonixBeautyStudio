#include "DevicesManager.h"
#include <QJSEngine>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include "ProbeDevice.h"

#if defined(Q_OS_WINDOWS)
    #include "WinWlanManager.h"
#elif defined(Q_OS_ANDROID)
    #include "AndroidWifiManager.h"
#endif
#include "TcpServer.h"

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
#if defined(Q_OS_ANDROID)
    connect(AndroidWifiManager::instance(), &AndroidWifiManager::wifiConnectedSuccessful, [] {
        qDebug() << "wifiConnectedSuccessful";
        TcpServer::instance()->connectToHost("192.168.0.10", 5061);
        if (!TcpServer::instance()->waitForConnected(3000))
        {
            qDebug() << "Tcp Connect failed:" << TcpServer::instance()->errorString();
        }
    });
    connect(AndroidWifiManager::instance(), &AndroidWifiManager::wifiConnectedFailed, [] {
        qDebug() << "wifiConnectedFailed";
    });
    connect(AndroidWifiManager::instance(), &AndroidWifiManager::wifiLost, [] {
        qDebug() << "wifiLost";
    });
#elif defined(Q_OS_WINDOWS)

#endif
}

void DevicesManager::connectToWifi(const QString& _ssid, const QString& _password)
{
#if defined(Q_OS_ANDROID)
    AndroidWifiManager::instance()->connectToWifi(_ssid, _password);
#elif defined(Q_OS_WINDOWS)
    WinWlanManager::instance()->connectToWifi(_ssid.toStdString(), _password.toStdString());
#endif
}

void DevicesManager::disconnectWifi()
{
#if defined(Q_OS_ANDROID)
    AndroidWifiManager::instance()->disconnectWifi();
#elif defined(Q_OS_WINDOWS)
    WinWlanManager::instance()->disconnectWifi();
#endif
}

QString DevicesManager::currentWifiName()
{
#if defined(Q_OS_ANDROID)
    return AndroidWifiManager::instance()->currentWifiName();
#elif defined(Q_OS_WINDOWS)
    return WinWlanManager::instance()->currentWifiName();
#endif
}

int DevicesManager::currentWifiSignalQuality()
{
#if defined(Q_OS_ANDROID)
    return AndroidWifiManager::instance()->currentWifiSignalQuality();
#elif defined(Q_OS_WINDOWS)
    return WinWlanManager::instance()->currentWifiSignalQuality();
#endif
}

void DevicesManager::refreshDevicesList()
{
    QVariantList          wifiListTmp{};
    QMap<QString, quint8> result{};
#if defined(Q_OS_ANDROID)
    result = AndroidWifiManager::instance()->getWifiList();
#elif defined(Q_OS_WINDOWS)
    result = WinWlanManager::instance()->getWifiList();
#endif
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
