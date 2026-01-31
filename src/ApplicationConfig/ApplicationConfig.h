_Pragma("once");
#include <QObject>
#include <QVariantMap>

class ApplicationConfig : public QObject
{
    Q_OBJECT
public:
    ~ApplicationConfig() noexcept = default;

public:
    static auto instance() noexcept -> ApplicationConfig*;

    auto init() noexcept -> void;

private:
    explicit(true) ApplicationConfig(QObject* _parent = nullptr);

    auto initAppStyle() noexcept -> void;

    auto initAppAttribute() noexcept -> void;

    auto initAppEnv() noexcept -> void;
};
