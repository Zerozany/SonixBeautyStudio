_Pragma("once");
#include <QQuickWindow>
#include <QExposeEvent>
#include <QtQml/qqmlregistration.h>

class AndroidWindow : public QQuickWindow
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit(true) AndroidWindow(QQuickWindow* _parent = nullptr);
    ~AndroidWindow() noexcept = default;

protected:
    void exposeEvent(QExposeEvent* _ev) override;

Q_SIGNALS:
    void appDisplayChanged(bool _tag);

private Q_SLOTS:
    void onAppDisplayChanged(bool _tag);

private:
};
