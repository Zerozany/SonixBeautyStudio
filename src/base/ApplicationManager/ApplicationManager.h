_Pragma("once");
#include "SoftwareManager.h"

class ApplicationManager : public SoftwareManager
{
    Q_OBJECT
public:
    static auto instance() noexcept -> ApplicationManager*;

    ~ApplicationManager() noexcept = default;

    Q_DISABLE_COPY_MOVE(ApplicationManager)

public:
    auto init() noexcept -> void;

private:
    explicit(true) ApplicationManager(SoftwareManager* _parent = nullptr);

    auto thirdConfig() noexcept -> void;

private:
    SoftwareStyle m_applicationStyle{
        .WindowsStyle{"Material"},
        .AndroidStyle{"Material"},
    };
};
