_Pragma("once");
#include "ViewEngineManager.h"
#include <QQmlApplicationEngine>

class ViewEngine : public ViewEngineManager
{
    Q_OBJECT
public:
    static auto instance(QQmlApplicationEngine& _qmlApplicationEngine, ViewEngineManager* _parent = nullptr) noexcept -> ViewEngine*;

    ~ViewEngine() noexcept = default;

    Q_DISABLE_COPY_MOVE(ViewEngine)

public:
    auto init() noexcept -> void;

private:
    explicit(true) ViewEngine(QQmlApplicationEngine& _qmlApplicationEngine, ViewEngineManager* _parent = nullptr);

private:
    auto connectSignal2Slot() noexcept -> void override;

    auto loadModule() noexcept -> void override;
};
