_Pragma("once");
#include "ViewEngineBase.h"
#include <QQmlApplicationEngine>

class ViewEngine : public ViewEngineBase
{
    Q_OBJECT
public:
    ~ViewEngine() noexcept = default;

public:
    static auto instance(QQmlApplicationEngine& _qmlApplicationEngine, ViewEngineBase* _parent = nullptr) noexcept -> ViewEngine*;

    auto init() noexcept -> void;

private:
    explicit(true) ViewEngine(QQmlApplicationEngine& _qmlApplicationEngine, ViewEngineBase* _parent = nullptr);

private:
    auto connectSignal2Slot() noexcept -> void override;

    auto engineLaod() noexcept -> void override;

Q_SIGNALS:

private:
};
