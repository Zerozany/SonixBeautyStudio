_Pragma("once");
#include <QObject>

class SystemConfig : public QObject
{
    Q_OBJECT
public:
    ~SystemConfig() noexcept = default;

public:
    static auto instance() noexcept -> SystemConfig*;

    auto init() noexcept -> void;

private:
    explicit(true) SystemConfig(QObject* _parent = nullptr);

    auto setAppEnv() noexcept -> void;

    auto setAppStyle() noexcept -> void;

    auto setAppAttribute() noexcept -> void;
};
