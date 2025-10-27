_Pragma("once");
#include <QObject>
#include <QQmlApplicationEngine>
#include <QGuiApplication>

class QQuickWindow;
class AndroidWindow;

class ViewEngine : public QObject
{
    Q_OBJECT
public:
    ~ViewEngine() noexcept = default;

public:
    static auto instance() noexcept -> ViewEngine*;

    static auto init(QGuiApplication* _guiApplication, QQmlApplicationEngine* _qmlApplicationEngine) noexcept -> void;

private:
    explicit(true) ViewEngine(QObject* _parent = nullptr);

private:
    static auto initMember(QGuiApplication* _guiApplication, QQmlApplicationEngine* _qmlApplicationEngine) noexcept -> void;

    static auto initEngine() noexcept -> void;

    static auto initWindow() noexcept -> void;

    static auto connectSignal2Slot() noexcept -> void;

Q_SIGNALS:
    void onCreate();
    void onResume();
    void onPause();
    void onDestroy();
    void onStart();
    void onRestart();
    void onStop();

private:
    inline static QGuiApplication*       m_guiApplication{nullptr};
    inline static QQmlApplicationEngine* m_qmlApplicationEngine{nullptr};
#if defined(Q_OS_ANDROID)
    inline static AndroidWindow* m_quickWindow{nullptr};
#elif defined(Q_OS_WINDOWS)
    inline static QQuickWindow* m_quickWindow{nullptr};
#endif
};
