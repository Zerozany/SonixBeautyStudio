_Pragma("once");
#include "ViewEngineManager.h"
#include <QQmlApplicationEngine>

class QmlEngineManager : public ViewEngineManager
{
    Q_OBJECT
public:
    static auto instance(QQmlApplicationEngine& _qmlApplicationEngine, ViewEngineManager* _parent = nullptr) noexcept -> QmlEngineManager*;

    ~QmlEngineManager() noexcept = default;

    Q_DISABLE_COPY_MOVE(QmlEngineManager)

public:
    auto init() noexcept -> void;

private:
    explicit(true) QmlEngineManager(QQmlApplicationEngine& _qmlApplicationEngine, ViewEngineManager* _parent = nullptr);

private:
    auto connectSignal2Slot() noexcept -> void override;

    auto loadModule() noexcept -> void override;
};
