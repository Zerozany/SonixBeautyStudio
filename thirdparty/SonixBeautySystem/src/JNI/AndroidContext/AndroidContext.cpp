#include "AndroidContext.h"
#include <QCoreApplication>

#if defined(Q_OS_ANDROID)
    #include <QJniObject>
#endif

auto AndroidContext::instance() noexcept -> AndroidContext*
{
    static AndroidContext androidContext{};
    return &androidContext;
}

auto AndroidContext::context() noexcept -> QJniObject*
{
#if defined(Q_OS_ANDROID)
    static QJniObject jniContext{QNativeInterface::QAndroidApplication::context()};
    if (!jniContext.isValid())
    {
        qDebug() << "Failed to get Activity context";
        return nullptr;
    }
    return &jniContext;
#endif
}

AndroidContext::AndroidContext(QObject* _parent)
{
}
