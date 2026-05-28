#include "DevicesManager.h"
#include <QJSEngine>
#include <QQmlEngine>
#include <QQmlApplicationEngine>

#if defined(Q_OS_ANDROID)
    #include "AndroidJNIManager.h"
    #include <QJniObject>
    #include <QJsonDocument>
    #include <QJsonValue>
    #include <QJsonObject>
    #include <QJsonArray>
#endif

DevicesManager* DevicesManager::create(QQmlEngine* _qmlEngine, QJSEngine* _qJSEngine)
{
    Q_UNUSED(_qJSEngine);
    static DevicesManager* deviceList{new DevicesManager{qobject_cast<QQmlApplicationEngine*>(_qmlEngine)}};
    return deviceList;
}

DevicesManager::DevicesManager(QObject* _parent) : QObject{_parent}
{
}

void DevicesManager::refreshDevicesList()
{
#if defined(Q_OS_ANDROID)
    AndroidJNIManager::instance()->setActivityUrl("com/sonixbeauty/module/JWifiManager");
    QJniObject            result{AndroidJNIManager::instance()->callJNIMethod<QJniObject>("getWifiList", "()Ljava/lang/String;")};
    QMap<QString, quint8> wifiViewMap{};
    QJsonDocument         doc{QJsonDocument::fromJson(result.toString().toUtf8())};
    for (const QJsonValue& value : doc.array())
    {
        wifiViewMap[value.toObject()["ssid"].toString()] = static_cast<quint8>(value.toObject()["level"].toInt());
    }
    for (const auto& [k, v] : wifiViewMap.toStdMap())
    {
        if (k.startsWith("US"))
        {
            qInfo() << k;
        }
    }
#endif
}
