_Pragma("once");
#include <QQuickWindow>
#include <QtQml/qqmlregistration.h>

#if defined(Q_OS_WINDOWS) && defined(_MSC_VER)
#ifdef SONIXEXPROTS
#define SONIXEX_API Q_DECL_EXPORT
#else
#define SONIXEX_API Q_DECL_IMPORT
#endif
#else
#define SONIXEX_API
#endif

class QExposeEvent;

class SONIXEX_API SonixBeautyWindow : public QQuickWindow
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit(true) SonixBeautyWindow(QQuickWindow* _parent = nullptr);
    ~SonixBeautyWindow() noexcept;

    static auto instance() noexcept -> SonixBeautyWindow*;

private:
    auto connectSignal2Slot() noexcept -> void;

    auto setSonixBeautyWindow(SonixBeautyWindow* _sonixBeautyWindow) noexcept -> void;

    auto setWindowPropertys() noexcept -> void;

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
    void onRestartChanged();

    void onPauseChanged();

private:
    inline static SonixBeautyWindow* m_instance{nullptr};
};
