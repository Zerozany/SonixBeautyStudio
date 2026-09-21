_Pragma("once");
#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QVariantList>
#include "QuickMacro.hpp"

#if defined(Q_OS_ANDROID)
    #include "AndroidJNIManager.h"
#elif defined(Q_OS_WINDOWS)
    #include "WinWlanManager.h"
#endif

class QJSEngine;
class QQmlEngine;

#if defined(Q_OS_ANDROID)
class AndroidJNIManager;
#endif

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

    void init() noexcept;

Q_SIGNALS:
    void devicesListChanged();

private:
    QVariantList m_devicesList{};

#if defined(Q_OS_ANDROID)
    AndroidJNIManager* m_androidWifiManager{nullptr};
#endif
};
