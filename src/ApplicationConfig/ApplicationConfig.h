_Pragma("once");
#include "ApplicationConfigBase.h"

class ApplicationConfig : public ApplicationConfigBase
{
    Q_OBJECT
public:
    ~ApplicationConfig() noexcept = default;

public:
    static auto instance() noexcept -> ApplicationConfig*;

    auto init() noexcept -> void;

private:
    explicit(true) ApplicationConfig(ApplicationConfigBase* _parent = nullptr);

    auto initAppStyle() noexcept -> void override;

    auto initAppAttribute() noexcept -> void override;

    auto initAppEnv() noexcept -> void override;
};
