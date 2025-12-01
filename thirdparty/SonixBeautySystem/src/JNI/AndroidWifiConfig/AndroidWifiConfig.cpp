#include "AndroidWifiConfig.h"
#include <QDebug>
#include <QCoreApplication>
#include <QStringList>

#if defined(Q_OS_ANDROID)
    #include <QJniObject>
    #include <QJniEnvironment>
    #include "AndroidContext.h"
#endif

#if defined(Q_OS_ANDROID)

extern "C" JNIEXPORT void JNICALL
Java_com_sonixbeauty_wifi_WifiRelativeInfo_connectSuccess(JNIEnv* env, jobject thiz, jint state)
{
    AndroidWifiConfig* androidWifiConfig{AndroidWifiConfig::instance()};
    if (androidWifiConfig)
    {
        Q_EMIT androidWifiConfig->wifiStateChanged(static_cast<AndroidWifiConfig::WifiState>(state));
    }
}
#endif

auto AndroidWifiConfig::instance() noexcept -> AndroidWifiConfig*
{
    static AndroidWifiConfig androidWifiConfig{};
    return &androidWifiConfig;
}

AndroidWifiConfig::AndroidWifiConfig(QObject* _parent) : QObject{_parent}
{
    std::invoke(&AndroidWifiConfig::init, this);
}

auto AndroidWifiConfig::init() noexcept -> void
{
#if defined(Q_OS_ANDROID)
    QJniObject* context{AndroidContext::instance()->context()};
    if (!context || !context->isValid())
    {
        qDebug() << "Failed to get valid context";
        return;
    }
    m_wifiObject = new QJniObject{"com/sonixbeauty/wifi/WifiRelativeInfo", "(Landroid/app/Activity;)V", context->object<jobject>(), this};
    if (!m_wifiObject->isValid())
    {
        qDebug() << "Cannot create Java helper instance";
        return;
    }
#endif
}

auto AndroidWifiConfig::searchWifiDevice() noexcept -> QMap<QString, quint8>
{
    QMap<QString, quint8> wifiMap{};
#if defined(Q_OS_ANDROID)
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
    QStringList wifiStrList{result.toString().replace("\"", "").split('\n', Qt::SkipEmptyParts)};
    if (wifiStrList.isEmpty())
    {
        return wifiMap;
    }
    for (QString& entry : wifiStrList)
    {
        QStringList parts{entry.replace(entry.lastIndexOf(' '), 1, ",").split(',')};
        wifiMap[parts[0].trimmed()] = parts[1].trimmed().toInt() + 100;
    }
#endif
    return wifiMap;
}

auto AndroidWifiConfig::curConnectedWifi() noexcept -> QString
{
    QString curConnectedWifiStr{};
#if defined(Q_OS_ANDROID)
    do
    {
        if (!m_wifiObject || !m_wifiObject->isValid())
        {
            break;
        }
        QJniObject result{m_wifiObject->callObjectMethod("getCurrentWifiSSID", "()Ljava/lang/String;")};
        if (!result.isValid())
        {
            curConnectedWifiStr = result.toString();
            break;
        }
        if (result.toString() == QString{"NULL"})
        {
            break;
        }
    } while (false);
#endif
    return curConnectedWifiStr;
}

auto AndroidWifiConfig::connectWifi2Ssid(const QString& _ssid, const QString& _password) noexcept -> void
{
#if defined(Q_OS_ANDROID)

    if (!m_wifiObject || !m_wifiObject->isValid())
    {
        return;
    }
    m_wifiObject->callMethod<void>("connectWifi", "(Ljava/lang/String;Ljava/lang/String;)V",
                                   QJniObject::fromString(_ssid).object<jstring>(),
                                   QJniObject::fromString(_password).object<jstring>());
#endif
}
