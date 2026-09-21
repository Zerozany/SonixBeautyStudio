_Pragma("once");
#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QVariantList>
#include "QuickMacro.hpp"

class QJSEngine;
class QQmlEngine;

class DevicesManager : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT
    QUICK_PROPERTY(QVariantList, m_devicesList, devicesList, devicesList, setDevicesList, devicesListChanged)
public:
    static DevicesManager* create(QQmlEngine* _qmlEngine = nullptr, QJSEngine* _qJSEngine = nullptr);

    ~DevicesManager() noexcept = default;

    Q_DISABLE_COPY_MOVE(DevicesManager)
public:
    Q_INVOKABLE void connectToWifi(const QString& _ssid, const QString& _password);

    Q_INVOKABLE void disconnectWifi();

    Q_INVOKABLE QString currentWifiName();

    Q_INVOKABLE int currentWifiSignalQuality();

    Q_INVOKABLE void refreshDevicesList();

private:
    explicit(true) DevicesManager(QObject* _parent = nullptr);

Q_SIGNALS:
    void devicesListChanged();

private:
    QVariantList m_devicesList{};
};
