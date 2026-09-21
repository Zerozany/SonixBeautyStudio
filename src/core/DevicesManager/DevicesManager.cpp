#include "DevicesManager.h"
#include <QJSEngine>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include "ProbeDevice.h"

#if defined(Q_OS_WINDOWS)
    #include "WinWlanManager.h"
#elif defined(Q_OS_ANDROID)
    #include "AndroidJNIManager.h"
    #include <QJniObject>
    #include <QJsonDocument>
    #include <QJsonValue>
    #include <QJsonArray>
#endif

namespace Private
{
#if defined(Q_OS_ANDROID)
    struct JNIConstTable
    {
        static constexpr const char* JNIWifiUrl{"com/sonixbeauty/module/JWifiManager"};
        static constexpr const char* JNIGetWifiList{"getWifiList"};
        static constexpr const char* JNIConnectTiWifi{"connectToWifi"};
        static constexpr const char* JNIDisconnectWifi{"disconnectWifi"};
        static constexpr const char* JNICurrentWifiName{"currentWifiName"};
        static constexpr const char* JNICurrentWifiSignalQuality{"currentWifiSignalQuality"};
    };
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
    std::invoke(&DevicesManager::init, this);
}

void DevicesManager::init() noexcept
{
#if defined(Q_OS_ANDROID)
    m_androidWifiManager = new AndroidJNIManager{this};
    m_androidWifiManager->setActivityUrl(Private::JNIConstTable::JNIWifiUrl);
#endif
}

void DevicesManager::connectToWifi(const QString& _ssid, const QString& _password)
{
#if defined(Q_OS_ANDROID)
    m_androidWifiManager->callJNIMethod<void>(Private::JNIConstTable::JNIConnectTiWifi, "(Ljava/lang/String;Ljava/lang/String;)V", QJniObject::fromString(_ssid).object<jstring>(), QJniObject::fromString(_password).object<jstring>());
#elif defined(Q_OS_WINDOWS)
    WinWlanManager::instance()->connectToWifi(_ssid.toStdString(), _password.toStdString());
#endif
}

void DevicesManager::disconnectWifi()
{
#if defined(Q_OS_ANDROID)
    m_androidWifiManager->callJNIMethod<void>(Private::JNIConstTable::JNIDisconnectWifi, "()V");
#elif defined(Q_OS_WINDOWS)
    WinWlanManager::instance()->disconnectWifi();
#endif
}

QString DevicesManager::currentWifiName()
{
#if defined(Q_OS_ANDROID)
    return m_androidWifiManager->callJNIMethod<QJniObject>(Private::JNIConstTable::JNICurrentWifiName, "()Ljava/lang/String;").toString();
#elif defined(Q_OS_WINDOWS)
    return WinWlanManager::instance()->currentWifiName();
#endif
}

int DevicesManager::currentWifiSignalQuality()
{
#if defined(Q_OS_ANDROID)
    return m_androidWifiManager->callJNIMethod<jint>(Private::JNIConstTable::JNICurrentWifiSignalQuality, "()I");
#elif defined(Q_OS_WINDOWS)
    return WinWlanManager::instance()->currentWifiSignalQuality();
#endif
}

void DevicesManager::refreshDevicesList()
{
    QVariantList wifiListTmp{};
#if defined(Q_OS_ANDROID)
    QJniObject    result{m_androidWifiManager->callJNIMethod<QJniObject>(Private::JNIConstTable::JNIGetWifiList, "()Ljava/lang/String;")};
    QJsonDocument doc{QJsonDocument::fromJson(result.toString().toUtf8())};
    for (const QJsonValue& _value : doc.array())
    {
        const QJsonArray pair{_value.toArray()};
        if (pair.size() < 2)
        {
            continue;
        }

        if (pair.at(0).toString().isEmpty())
        {
            continue;
        }
        wifiListTmp.append(QVariantMap{{QStringLiteral("ssid"), pair.at(0).toString()}, {QStringLiteral("level"), pair.at(1).toInt()}});
    }
#elif defined(Q_OS_WINDOWS)
    const QMap<QString, quint8> result{WinWlanManager::instance()->getWifiList()};
    for (const auto& [_ssid, _level] : result.toStdMap())
    {
        wifiListTmp.append(QVariantMap{{QStringLiteral("ssid"), _ssid}, {QStringLiteral("level"), _level}});
    }
#endif
    if (wifiListTmp.isEmpty())
    {
        return;
    }
    this->setDevicesList(wifiListTmp);
}
