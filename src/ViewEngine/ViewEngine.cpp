#include "ViewEngine.h"
#include <QTimer>
#include <QQuickWindow>

#if defined(Q_OS_ANDROID)
#include <QJniObject>
#include <QJniEnvironment>
#include "AndroidWindow.h"

extern "C" {

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyCreate(JNIEnv*, jclass)
    {
        qDebug() << "C++ 收到 onCreate通知";
        Q_EMIT ViewEngine::instance()->onCreate();
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyStart(JNIEnv*, jclass)
    {
        qDebug() << "C++ 收到 Start";
        Q_EMIT ViewEngine::instance()->onStart();
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyStop(JNIEnv*, jclass)
    {
        qDebug() << "C++ 收到 Stop";
        Q_EMIT ViewEngine::instance()->onStop();
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyRestart(JNIEnv*, jclass)
    {
        qDebug() << "C++ 收到 Restart";
        Q_EMIT ViewEngine::instance()->onRestart();
    }
}

#endif

auto ViewEngine::instance() noexcept -> ViewEngine*
{
    static ViewEngine viewEngine{};
    return &viewEngine;
}

auto ViewEngine::init(QGuiApplication* _guiApplication, QQmlApplicationEngine* _qmlApplicationEngine) noexcept -> void
{
    std::invoke(&ViewEngine::initMember, _guiApplication, _qmlApplicationEngine);
    std::invoke(&ViewEngine::initEngine);
    std::invoke(&ViewEngine::initWindow);
    std::invoke(&ViewEngine::connectSignal2Slot);
}

ViewEngine::ViewEngine(QObject* _parent) : QObject{_parent}
{
}

auto ViewEngine::initMember(QGuiApplication* _guiApplication, QQmlApplicationEngine* _qmlApplicationEngine) noexcept -> void
{
    if (!_guiApplication)
    {
        return;
    }
    if (!_qmlApplicationEngine)
    {
        return;
    }
    m_guiApplication       = _guiApplication;
    m_qmlApplicationEngine = _qmlApplicationEngine;
}

auto ViewEngine::initEngine() noexcept -> void
{
    if (!m_qmlApplicationEngine)
    {
        return;
    }
    m_qmlApplicationEngine->addImportPath("qrc:/");
    m_qmlApplicationEngine->load(QUrl("qrc:/SonixBeautyStudio/view/Main.qml"));
}

auto ViewEngine::initWindow() noexcept -> void
{
    if (m_qmlApplicationEngine->rootObjects().isEmpty())
    {
        return;
    }
#if defined(Q_OS_ANDROID)
    m_quickWindow = qobject_cast<AndroidWindow*>(m_qmlApplicationEngine->rootObjects().first());
#elif defined(Q_OS_WINDOWS)
    m_quickWindow = qobject_cast<QQuickWindow*>(m_qmlApplicationEngine->rootObjects().first());
#endif
    if (!m_quickWindow)
    {
        return;
    }
    m_quickWindow->setPersistentSceneGraph(true);
    m_quickWindow->setPersistentGraphics(true);
}

auto ViewEngine::connectSignal2Slot() noexcept -> void
{
#if defined(Q_OS_ANDROID)

    connect(ViewEngine::instance(), &ViewEngine::onStart, ViewEngine::instance(), [] {
        QMetaObject::invokeMethod(qApp, [] { QTimer::singleShot(300, [] {
                                                 if (m_quickWindow && m_quickWindow->isSceneGraphInitialized())
                                                 {
                                                     m_quickWindow->show();
                                                 }
                                             }); }, Qt::QueuedConnection);
    });

    connect(ViewEngine::instance(), &ViewEngine::onStop, ViewEngine::instance(), [] {
        QMetaObject::invokeMethod(qApp, [] {
        if (m_quickWindow)
            m_quickWindow->hide(); }, Qt::QueuedConnection);
    });

    connect(ViewEngine::instance(), &ViewEngine::onRestart, ViewEngine::instance(), [] {
        QMetaObject::invokeMethod(qApp, [] { QTimer::singleShot(300, [] {
                                                 if (m_quickWindow && m_quickWindow->isSceneGraphInitialized())
                                                 {
                                                     m_quickWindow->show();
                                                 }
                                             }); }, Qt::QueuedConnection);
    });

    // connect(m_guiApplication, &QGuiApplication::applicationStateChanged, [](Qt::ApplicationState _state) {
    //     switch (_state)
    //     {
    //         case Qt::ApplicationActive:
    //         {
    //             QTimer::singleShot(800, [] {
    //                 if (m_quickWindow->isSceneGraphInitialized())
    //                 {
    //                     m_quickWindow->show();
    //                 }
    //             });
    //             break;
    //         }
    //         case Qt::ApplicationHidden:
    //         {
    //             [[fallthrough]];
    //         }
    //         case Qt::ApplicationInactive:
    //         {
    //             [[fallthrough]];
    //         }
    //         case Qt::ApplicationSuspended:
    //         {
    //             m_quickWindow->hide();
    //             break;
    //         }
    //         default:
    //         {
    //             std::unreachable();
    //         }
    //     }
    // });
#endif
}
