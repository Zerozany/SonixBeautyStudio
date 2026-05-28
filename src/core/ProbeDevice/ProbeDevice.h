_Pragma("once");
#include <QObject>
#include <QtQml/qqmlregistration.h>
#include "PublicDefine.hpp"

class ProbeDevice : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    enum class DeviceType
    {
        UnKnow,
        Usb,
        Wifi,
    };
    Q_ENUM(DeviceType)

    QUICK_PROPERTY(QString, m_systemName, systemName, systemName, setSystemName, systemNameChanged)
    QUICK_PROPERTY(QString, m_vid, vid, vid, setVid, vidChanged)
    QUICK_PROPERTY(QString, m_pid, pid, pid, setPid, pidChanged)
    QUICK_PROPERTY(QString, m_ssid, ssid, ssid, setSsid, ssidChanged)
    QUICK_PROPERTY(DeviceType, m_deviceType, deviceType, deviceType, setDeviceType, deviceTypeChanged)
    QUICK_PROPERTY(QString, m_probeType, probeType, probeType, setProbeType, probeTypeChanged)
    QUICK_PROPERTY(QString, m_transducerName, transducerName, transducerName, setTransducerName, transducerNameChanged)
    QUICK_PROPERTY(quint8, m_signaleQuality, signaleQuality, signaleQuality, setSignaleQuality, signaleQualityChanged)

public:
    explicit(true) ProbeDevice(QObject* _parent = nullptr);

    ~ProbeDevice() noexcept = default;

Q_SIGNALS:
    void systemNameChanged();
    void vidChanged();
    void pidChanged();
    void ssidChanged();
    void deviceTypeChanged();
    void probeTypeChanged();
    void transducerNameChanged();
    void signaleQualityChanged();

private:
    QString    m_systemName{};
    QString    m_vid{};
    QString    m_pid{};
    QString    m_ssid{};
    DeviceType m_deviceType{};
    QString    m_probeType{};
    QString    m_transducerName{};
    quint8     m_signaleQuality{};
};
