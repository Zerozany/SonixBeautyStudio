#include "DevicesManager.h"
#include <QJSEngine>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include "ProbeDevice.h"

#if defined(Q_OS_WINDOWS)
    #include "WinWifiManager.h"
#elif defined(Q_OS_ANDROID)
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
    QVariantList          devicesList{};
    QMap<QString, quint8> wifiList{};
#if defined(Q_OS_WINDOWS)
    wifiList = WinWifiManager::instance()->getWifiList();
#elif defined(Q_OS_ANDROID)
    AndroidJNIManager::instance()->setActivityUrl("com/sonixbeauty/module/JWifiManager");
    QJniObject result{AndroidJNIManager::instance()->callJNIMethod<QJniObject>("getWifiList", "()Ljava/lang/String;")};
    for (QJsonDocument doc{QJsonDocument::fromJson(result.toString().toUtf8())}; const QJsonValue& value : doc.array())
    {
        wifiList.insert(value.toObject()["ssid"].toString(), static_cast<quint8>(value.toObject()["level"].toInt()));
    }
#endif
    for (const auto& [_wifiName, _level] : wifiList.toStdMap())
    {
        if (!_wifiName.startsWith("US"))
        {
            continue;
        }
        ProbeDevice* probeDevice{new ProbeDevice{this}};
        probeDevice->setSystemName(_wifiName);
        probeDevice->setDeviceType(ProbeDevice::DeviceType::Wifi);
        probeDevice->setSignaleQuality(_level);
        QString typeNumber{_wifiName.mid(2, 2)};
        if (typeNumber == "12")
        {
            probeDevice->setSsid(QString{_wifiName}.replace(2, 2, "01"));
            probeDevice->setProbeType("linear");
            probeDevice->setTransducerName("linear");
            /* 需复制一个对象类 */
        }
        else if (typeNumber == "00")
        {
            probeDevice->setSsid(_wifiName);
            probeDevice->setProbeType("linear");
            probeDevice->setTransducerName("L12-18N");
        }
        else if (typeNumber == "01")
        {
            probeDevice->setSsid(_wifiName);
            probeDevice->setProbeType("linear");
            probeDevice->setTransducerName("rhinitis");
        }
        else if (typeNumber == "02")
        {
            probeDevice->setSsid(_wifiName);
            probeDevice->setProbeType("convex");
            probeDevice->setTransducerName("convex");
        }
        else if (typeNumber == "03")
        {
            probeDevice->setSsid(_wifiName);
            probeDevice->setProbeType("phased");
            probeDevice->setTransducerName("phased");
        }
        else if (typeNumber == "06")
        {
            /* 新设备可读写出厂设置 */
            probeDevice->setSsid(_wifiName);
            probeDevice->setProbeType("device");
            probeDevice->setTransducerName("device");
        }
        devicesList.append(QVariant::fromValue(probeDevice));
    }
    this->setDevicesList(devicesList);

#if false
    for (int i = 0; i < m_devicesList.size(); ++i)
    {
        QVariant     variant = m_devicesList[i];
        ProbeDevice* device  = variant.value<ProbeDevice*>();
        if (device)
        {
            qInfo() << "  systemName:" << device->systemName();
            qInfo() << "  SSID:" << device->ssid();
            qInfo() << "  DeviceType:" << static_cast<ProbeDevice::DeviceType>(device->deviceType());
            qInfo() << "  SignalQuality:" << device->signaleQuality();
            qInfo() << "  VID:" << device->vid();
            qInfo() << "  PID:" << device->pid();
            qInfo() << "  probeType:" << device->probeType();
            qInfo() << "  transducerName:" << device->transducerName();
        }
    }
#endif
}
