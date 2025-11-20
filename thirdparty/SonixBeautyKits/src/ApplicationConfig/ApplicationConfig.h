_Pragma("once");
#include <QObject>

class ApplicationConfig : public QObject
{
    Q_OBJECT
public:
    ~ApplicationConfig() noexcept = default;

public:
    static auto instance() noexcept -> ApplicationConfig*;

    auto init() noexcept -> void;

    auto setAppEnv(const char* _envName, const QByteArray& _value) noexcept -> void;

    auto setAppAttribute(const Qt::ApplicationAttribute _attribute, bool _switch = true) noexcept -> void;

private:
    explicit(true) ApplicationConfig(QObject* _parent = nullptr);

    auto initAppEnv() noexcept -> void;

    auto initAppStyle() noexcept -> void;

    auto initAppAttribute() noexcept -> void;
};
