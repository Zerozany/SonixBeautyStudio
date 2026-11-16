_Pragma("once");
#include "SoftwareManager.h"

class ApplicationConfig : public SoftwareManager
{
    Q_OBJECT
public:
    static auto instance() noexcept -> ApplicationConfig*;

    ~ApplicationConfig() noexcept = default;

    Q_DISABLE_COPY_MOVE(ApplicationConfig)

public:
    auto init() noexcept -> void;

private:
    explicit(true) ApplicationConfig(SoftwareManager* _parent = nullptr);

private:
    SoftwareStyle m_applicationStyle{
        .WindowsStyle{"Material"},
        .AndroidStyle{"Material"},
    };
};
