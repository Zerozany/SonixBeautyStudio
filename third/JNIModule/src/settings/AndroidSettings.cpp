#include "AndroidSettings.h"
#include <QDebug>
#include <QCoreApplication>

#if defined(ANDROID)
#include <QJniObject>
#include <QJniEnvironment>

auto AndroidSettings::instance() noexcept -> AndroidSettings*
{
    static AndroidSettings* androidSettings{new AndroidSettings{}};
    return androidSettings;
}

AndroidSettings::AndroidSettings(QObject* _parent) : QObject{_parent}
{
    std::invoke(&AndroidSettings::init, this);
}

auto AndroidSettings::init() noexcept -> void
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
    m_settingObject = new QJniObject{"com/sonixbeauty/settings/AppSettings", "(Landroid/app/Activity;)V", activity.object<jobject>(), this};
    if (!m_settingObject->isValid())
    {
        qDebug() << "Cannot create Java helper instance";
        return;
    }
}

auto AndroidSettings::setScreenBrightness(float _value) noexcept -> void
{
    m_settingObject->callMethod<void>("setSystemBrightness", "(I)V", jint(_value));
}

#endif
