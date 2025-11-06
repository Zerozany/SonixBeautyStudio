_Pragma("once");
#include <QQuickWindow>
#include <QtQml/qqmlregistration.h>

class QExposeEvent;

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

    auto setSonixBeautyWindow(SonixBeautyWindow* _sonixBeautyWindow) noexcept -> void;

    auto setWindowPropertys() noexcept -> void;

protected:
    void exposeEvent(QExposeEvent* _ev) override;

Q_SIGNALS:

private Q_SLOTS:

private:
    inline static SonixBeautyWindow* m_instance{nullptr};
};
