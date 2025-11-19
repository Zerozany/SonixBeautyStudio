#include "AndroidWifiConfig.h"
#include <QDebug>
#include <QCoreApplication>
#include <QStringList>

#if defined(ANDROID)
#include <QJniObject>
#include <QJniEnvironment>

extern "C" JNIEXPORT void JNICALL
Java_com_sonixbeauty_wifi_WifiRelativeInfo_connectSuccess(JNIEnv* env, jobject thiz, jint state)
{
    AndroidWifiConfig* obj{AndroidWifiConfig::instance()};
    if (obj)
    {
        Q_EMIT obj->wifiStateChanged(static_cast<AndroidWifiConfig::WifiState>(state));
    }
}

auto AndroidWifiConfig::instance() noexcept -> AndroidWifiConfig*
{
    static AndroidWifiConfig* androidWifiConfig{new AndroidWifiConfig{}};
    return androidWifiConfig;
}

AndroidWifiConfig::AndroidWifiConfig(QObject* _parent) : QObject{_parent}
{
    std::invoke(&AndroidWifiConfig::init, this);
    // 延迟调用，保证 Activity 已启动
}

auto AndroidWifiConfig::init() noexcept -> void
{
    // 获取 Android Activity
    auto androidApp{QCoreApplication::instance()->nativeInterface<QNativeInterface::QAndroidApplication>()};
    if (!androidApp)
    {
        qDebug() << "Failed to get QAndroidApplication";
        return;
    }
    QJniObject activity{androidApp->context()};
    if (!activity.isValid())
    {
        qDebug() << "Failed to get Activity context";
        return;
    }
    m_wifiObject = new QJniObject{"com/sonixbeauty/wifi/WifiRelativeInfo", "(Landroid/app/Activity;)V", activity.object<jobject>(), this};
    if (!m_wifiObject->isValid())
    {
        qDebug() << "Cannot create Java helper instance";
        return;
    }
}

auto AndroidWifiConfig::searchWifiDevice() noexcept -> QMap<QString, quint8>
{
    QMap<QString, quint8> wifiMap{};
    if (!m_wifiObject || !m_wifiObject->isValid())
    {
        return wifiMap;
    }
    QJniObject result{m_wifiObject->callObjectMethod("scanWifiList", "()Ljava/lang/String;")};
    if (!result.isValid())
    {
        return wifiMap;
    }
    if (result.toString() == QString{"NULL"})
    {
        return wifiMap;
    }
    QStringList wifiStrList{result.toString().split(',', Qt::SkipEmptyParts)};
    for (const QString& entry : wifiStrList)
    {
        QStringList wifiGroup{entry.split(' ', Qt::SkipEmptyParts)};
        if (wifiGroup.size() == 2)
        {
            wifiMap[QString::fromUtf8(wifiGroup[0].toUtf8())] = wifiGroup[1].toInt() + 100;
        }
    }
    return wifiMap;
}

auto AndroidWifiConfig::curConnectedWifi() noexcept -> QString
{
    QString curConnectedWifiStr{};
    if (!m_wifiObject || !m_wifiObject->isValid())
    {
        return curConnectedWifiStr;
    }
    QJniObject result{m_wifiObject->callObjectMethod("getCurrentWifiSSID", "()Ljava/lang/String;")};
    if (!result.isValid())
    {
        return curConnectedWifiStr;
    }
    if (result.toString() == QString{"NULL"})
    {
        return curConnectedWifiStr;
    }
    return result.toString();
}

auto AndroidWifiConfig::connectWifi2Ssid(const QString& _ssid, const QString& _password) noexcept -> void
{
    if (!m_wifiObject || !m_wifiObject->isValid())
    {
        return;
    }
    m_wifiObject->callMethod<void>("connectWifi", "(Ljava/lang/String;Ljava/lang/String;)V",
                                   QJniObject::fromString(_ssid).object<jstring>(),
                                   QJniObject::fromString(_password).object<jstring>());
}

#endif
