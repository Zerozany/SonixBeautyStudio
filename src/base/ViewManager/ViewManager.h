_Pragma("once");
#include "ViewEngineManager.h"
#include <QQmlApplicationEngine>

class ViewManager : public ViewEngineManager
{
    Q_OBJECT
public:
    static auto instance(QQmlApplicationEngine& _qmlApplicationEngine, ViewEngineManager* _parent = nullptr) noexcept -> ViewManager*;

    ~ViewManager() noexcept = default;

    Q_DISABLE_COPY_MOVE(ViewManager)

public:
    auto init() noexcept -> void;

private:
    explicit(true) ViewManager(QQmlApplicationEngine& _qmlApplicationEngine, ViewEngineManager* _parent = nullptr);

private:
    auto connectSignal2Slot() noexcept -> void override;

    auto loadModule() noexcept -> void override;
};
