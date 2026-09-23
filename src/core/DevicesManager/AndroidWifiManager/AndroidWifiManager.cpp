#include "AndroidWifiManager.h"
#include <QMap>

#if defined(Q_OS_ANDROID)
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

#if defined(Q_OS_ANDROID)
extern "C" {
    JNIEXPORT void JNICALL Java_com_sonixbeauty_module_JWifiManager_QWifiConnectedSuccessful(JNIEnv*, jclass)
    {
        QMetaObject::invokeMethod(AndroidWifiManager::instance(), "wifiConnectedSuccessful", Qt::QueuedConnection);
    }

    JNIEXPORT void JNICALL Java_com_sonixbeauty_module_JWifiManager_QWifiConnectedFailed(JNIEnv*, jclass)
    {
        QMetaObject::invokeMethod(AndroidWifiManager::instance(), "wifiConnectedFailed", Qt::QueuedConnection);
    }

    JNIEXPORT void JNICALL Java_com_sonixbeauty_module_JWifiManager_QWifiLost(JNIEnv*, jclass)
    {
        QMetaObject::invokeMethod(AndroidWifiManager::instance(), "wifiLost", Qt::QueuedConnection);
    }
}

#endif

auto AndroidWifiManager::instance(QObject* _parent) noexcept -> AndroidWifiManager*
{
    static AndroidWifiManager* androidWifiManager{new AndroidWifiManager{_parent}};
    return androidWifiManager;
}

AndroidWifiManager::AndroidWifiManager(QObject* _parent) : AndroidJNIManager{_parent}
{
    std::invoke(&AndroidWifiManager::init, this);
}

auto AndroidWifiManager::init() noexcept -> void
{
#if defined(Q_OS_ANDROID)
    this->setActivityUrl(Private::JNIConstTable::JNIWifiUrl);
#endif
}

void AndroidWifiManager::connectToWifi(const QString& _ssid, const QString& _password)
{
#if defined(Q_OS_ANDROID)
    this->callJNIMethod<void>(Private::JNIConstTable::JNIConnectTiWifi, "(Ljava/lang/String;Ljava/lang/String;)V", QJniObject::fromString(_ssid).object<jstring>(), QJniObject::fromString(_password).object<jstring>());
#endif
}

void AndroidWifiManager::disconnectWifi()
{
#if defined(Q_OS_ANDROID)
    this->callJNIMethod<void>(Private::JNIConstTable::JNIDisconnectWifi, "()V");
#endif
}

QString AndroidWifiManager::currentWifiName()
{
#if defined(Q_OS_ANDROID)
    return this->callJNIMethod<QJniObject>(Private::JNIConstTable::JNICurrentWifiName, "()Ljava/lang/String;").toString();
#endif
    return QString{};
}

int AndroidWifiManager::currentWifiSignalQuality()
{
#if defined(Q_OS_ANDROID)
    return this->callJNIMethod<jint>(Private::JNIConstTable::JNICurrentWifiSignalQuality, "()I");
#endif
    return int{};
}

QMap<QString, quint8> AndroidWifiManager::getWifiList()
{
    QMap<QString, quint8> wifiList{};
#if defined(Q_OS_ANDROID)
    QJniObject    result{this->callJNIMethod<QJniObject>(Private::JNIConstTable::JNIGetWifiList, "()Ljava/lang/String;")};
    QJsonDocument doc{QJsonDocument::fromJson(result.toString().toUtf8())};
    for (const QJsonValue& _value : doc.array())
    {
        const QJsonArray pair{_value.toArray()};
        if (pair.size() < 2)
        {
            continue;
        }
        const QString ssid{pair.at(0).toString()};
        if (ssid.isEmpty())
        {
            continue;
        }
        wifiList.insert(ssid, static_cast<quint8>(pair.at(1).toInt()));
    }
#endif
    return wifiList;
}
