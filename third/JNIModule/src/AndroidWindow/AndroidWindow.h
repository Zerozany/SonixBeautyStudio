_Pragma("once");
#include <QQuickWindow>
#include <QtQml/qqmlregistration.h>

class QExposeEvent;

class AndroidWindow : public QQuickWindow
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit(true) AndroidWindow(QQuickWindow* _parent = nullptr);
    ~AndroidWindow() noexcept;

    static auto instance() noexcept -> AndroidWindow*;

private:
    auto connectSignal2Slot() noexcept -> void;

protected:
    void exposeEvent(QExposeEvent* _ev) override;

Q_SIGNALS:
    void onCreate();

    void onStart();

    void onResume();

    void onPause();

    void onStop();

    void onDestroy();

    void onRestart();

private Q_SLOTS:
    void onStartChanged();

    void onStopChanged();

    void onRestartChanged();

private:
    inline static AndroidWindow* m_instance{nullptr};
};
