_Pragma("once");
#include <QObject>

class QQmlApplicationEngine;
class QGuiApplication;
#if defined(Q_OS_ANDROID)
class SonixBeautyWindow;
#elif defined(Q_OS_WINDOWS)
class SonixBeautyWindow;
#endif

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
    static auto initObject(QGuiApplication* _guiApplication, QQmlApplicationEngine* _qmlApplicationEngine) noexcept -> void;

    static auto engineSetting() noexcept -> void;

    static auto windowSetting() noexcept -> void;

    static auto connectSignal2Slot() noexcept -> void;

Q_SIGNALS:

private:
    inline static QGuiApplication*       m_guiApplication{nullptr};
    inline static QQmlApplicationEngine* m_qmlApplicationEngine{nullptr};
#if defined(Q_OS_ANDROID)
    inline static SonixBeautyWindow* m_quickWindow{nullptr};
#elif defined(Q_OS_WINDOWS)
    inline static SonixBeautyWindow* m_quickWindow{nullptr};
#endif
};
