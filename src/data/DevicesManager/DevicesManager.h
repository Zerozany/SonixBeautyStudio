_Pragma("once");
#include <QObject>
#include <QtQml/qqmlregistration.h>

class QJSEngine;
class QQmlEngine;
class QQmlApplicationEngine;

class DevicesManager : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT
public:
    static DevicesManager* create(QQmlEngine* _qmlEngine = nullptr, QJSEngine* _qJSEngine = nullptr);

    ~DevicesManager() noexcept = default;

    Q_DISABLE_COPY_MOVE(DevicesManager)

protected:
    explicit(true) DevicesManager(QObject* _parent = nullptr);
};
