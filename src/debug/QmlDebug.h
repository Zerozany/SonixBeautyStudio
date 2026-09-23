_Pragma("once");
#include <QObject>
#include <QtQml/qqmlregistration.h>

#include "QuickMacro.hpp"

class QJSEngine;
class QQmlEngine;

class QmlDebug : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT
    QUICK_PROPERTY(QByteArray, m_sendData, sendData, sendData, setSendData, sendDataChanged)
public:
    static QmlDebug* create(QQmlEngine* _qmlEngine = nullptr, QJSEngine* _qJSEngine = nullptr);

    ~QmlDebug() noexcept = default;

    Q_DISABLE_COPY_MOVE(QmlDebug)
public:
    Q_INVOKABLE void sendDatas();

private:
    explicit(true) QmlDebug(QObject* _parent = nullptr);

Q_SIGNALS:
    void sendDataChanged();

private:
    QByteArray m_sendData{};
};
