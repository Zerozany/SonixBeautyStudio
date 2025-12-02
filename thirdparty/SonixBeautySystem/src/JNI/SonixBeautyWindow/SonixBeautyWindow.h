_Pragma("once");
#include <QQuickWindow>
#include <QtQml/qqmlregistration.h>

class SonixBeautyWindow : public QQuickWindow
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit(true) SonixBeautyWindow(QQuickWindow* _parent = nullptr);
    ~SonixBeautyWindow() noexcept;

    static auto instance() noexcept -> SonixBeautyWindow*;

private:
    auto connectSignal2Slot() noexcept -> void;

    auto setSonixBeautyWindow() noexcept -> void;

    auto setWindowPropertys() noexcept -> void;

Q_SIGNALS:
    void activityVisibileChanged(bool _activityVisibile);

private Q_SLOTS:
    void onActivityVisibileChanged(bool _activityVisibile);

private:
    inline static SonixBeautyWindow* m_instance{nullptr};
};
