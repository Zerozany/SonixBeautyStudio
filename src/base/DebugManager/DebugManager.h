_Pragma("once");
#include <QObject>
#include <QtQml/qqmlregistration.h>

#include "QuickMacro.hpp"

class QJSEngine;
class QQmlEngine;

class DebugManager : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT
    QUICK_PROPERTY(QByteArray, m_sendData, sendData, sendData, setSendData, sendDataChanged)
    QUICK_PROPERTY(QByteArray, m_recvData, recvData, recvData, setRecvData, recvDataChanged)
public:
    static DebugManager* create(QQmlEngine* _qmlEngine = nullptr, QJSEngine* _qJSEngine = nullptr);

    ~DebugManager() noexcept = default;

    Q_DISABLE_COPY_MOVE(DebugManager)
public:
    Q_INVOKABLE void sendDatas();

private:
    explicit(true) DebugManager(QObject* _parent = nullptr);

Q_SIGNALS:
    void sendDataChanged();
    void recvDataChanged();

private:
    QByteArray m_sendData{};
    QByteArray m_recvData{};
};
