#include "AndroidSystem.h"
#include <QDebug>
#include <QCoreApplication>

#if defined(Q_OS_ANDROID)
    #include <QJniObject>
    #include <QJniEnvironment>
    #include "AndroidContext.h"
#endif

auto AndroidSystem::instance() noexcept -> AndroidSystem*
{
    static AndroidSystem androidSettings{};
    return &androidSettings;
}

AndroidSystem::AndroidSystem(QObject* _parent) : QObject{_parent}
{
    std::invoke(&AndroidSystem::init, this);
}

auto AndroidSystem::init() noexcept -> void
{
#if defined(Q_OS_ANDROID)
    QJniObject* context{AndroidContext::instance()->context()};
    if (!context || !context->isValid())
    {
        qDebug() << "Failed to get valid context";
        return;
    }
    m_settingObject = new QJniObject{"com/sonixbeauty/system/SystemControl", "(Landroid/app/Activity;)V", context->object<jobject>(), this};
    if (!m_settingObject->isValid())
    {
        qDebug() << "Cannot create Java helper instance";
        return;
    }
#endif
}

auto AndroidSystem::setScreenBrightness(float _value) noexcept -> void
{
#if defined(Q_OS_ANDROID)
    m_settingObject->callMethod<void>("setSystemBrightness", "(I)V", jint(_value));
#endif
}
