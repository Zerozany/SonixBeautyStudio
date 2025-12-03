_Pragma("once");
#include <QQuickWindow>
#include <QtQml/qqmlregistration.h>

#if defined(Q_OS_WINDOWS) && defined(_MSC_VER)
    #ifdef SONIXBEAUTYSYSTEM
        #define SONIXEX_API Q_DECL_EXPORT
    #else
        #define SONIXEX_API Q_DECL_IMPORT
    #endif
#else
    #define SONIXEX_API
#endif

class SONIXEX_API SonixBeautyWindow : public QQuickWindow
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit(true) SonixBeautyWindow(QQuickWindow* _parent = nullptr);
    ~SonixBeautyWindow() noexcept = default;

    static auto instance() noexcept -> SonixBeautyWindow*;

private:
    auto connectSignal2Slot() noexcept -> void;

    auto setWindowPropertys() noexcept -> void;

Q_SIGNALS:

private Q_SLOTS:

private:
};
