_Pragma("once");
#include <QQmlApplicationEngine>

class QmlEngineManager : public QObject
{
    Q_OBJECT
public:
    static auto instance(QQmlApplicationEngine& _qmlApplicationEngine, QObject* _parent = nullptr) noexcept -> QmlEngineManager*;

    ~QmlEngineManager() noexcept = default;

    Q_DISABLE_COPY_MOVE(QmlEngineManager)

public:
    auto init() noexcept -> void;

private:
    explicit(true) QmlEngineManager(QQmlApplicationEngine& _qmlApplicationEngine, QObject* _parent = nullptr);

private:
    auto connectSignal2Slot() noexcept -> void;

private:
    QQmlApplicationEngine& m_qmlApplicationEngine;
};
