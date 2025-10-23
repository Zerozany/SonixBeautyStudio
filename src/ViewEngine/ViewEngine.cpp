#include "ViewEngine.h"
#include <QQuickWindow>
#include <QTimer>

#if defined(Q_OS_ANDROID)
#include <QJniObject>
#include <QJniEnvironment>

extern "C" {

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyCreate(JNIEnv*, jclass)
    {
        qDebug() << "C++ 收到 onCreate通知";
        Q_EMIT ViewEngine::instance()->onCreate();
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyResume(JNIEnv*, jclass)
    {
        qDebug() << "C++ 收到 onResume通知";
        Q_EMIT ViewEngine::instance()->onResume();
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyPause(JNIEnv*, jclass)
    {
        qDebug() << "C++ 收到 onPause通知";
        Q_EMIT ViewEngine::instance()->onPause();
    }

    JNIEXPORT void JNICALL
    Java_com_sonixbeauty_activity_AppActivity_nativeNotifyDestroy(JNIEnv*, jclass)
    {
        qDebug() << "C++ 收到 onDestroy通知";
        Q_EMIT ViewEngine::instance()->onDestroy();
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
    m_quickWindow = qobject_cast<AndroidWindow*>(m_qmlApplicationEngine->rootObjects().first());
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

    connect(ViewEngine::instance(), &ViewEngine::onResume, ViewEngine::instance(), [] {
        // if (!m_quickWindow->isExposed())
        // {
        //     qDebug() << "DDDDDD";
        //     Q_EMIT ViewEngine::instance()->onResume();
        // }
        // m_quickWindow->show();
    });

    connect(ViewEngine::instance(), &ViewEngine::onPause, ViewEngine::instance(), [] {
        // m_quickWindow->hide();
    });

    connect(ViewEngine::instance(), &ViewEngine::onDestroy, ViewEngine::instance(), [] {
    });

    // connect(m_guiApplication, &QGuiApplication::applicationStateChanged, [this](Qt::ApplicationState _state) {
    //     switch (_state)
    //     {
    //         case Qt::ApplicationActive:
    //         {
    //             QTimer::singleShot(800, [this]() {
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
