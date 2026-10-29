#include "LoginConfig.h"

namespace Private
{
    static constexpr const char* LoginSeverPath{":/config/settings/loginServer.ini"};
}  // namespace Private

LoginConfig* LoginConfig::instance(QObject* _parent) noexcept
{
    static LoginConfig* loginConfig{new LoginConfig{Private::LoginSeverPath, _parent}};
    return loginConfig;
}

LoginConfig::LoginConfig(const QString& _fileName, QObject* _parent) : ConfigSetting{_fileName, QSettings::IniFormat, _parent}
{
    ConfigSetting::init();
}
