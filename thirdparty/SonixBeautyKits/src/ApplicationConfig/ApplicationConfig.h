_Pragma("once");
#include <QObject>

#if defined(Q_OS_WINDOWS) && defined(_MSC_VER)
#    ifndef SONIXEX_API
#        ifdef SONIXEXPROTS
#            define SONIXEX_API Q_DECL_EXPORT
#        else
#            define SONIXEX_API Q_DECL_IMPORT
#        endif
#    endif
#else
#    ifndef SONIXEX_API
#        define SONIXEX_API
#    endif
#endif

class SONIXEX_API ApplicationConfig : public QObject
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
