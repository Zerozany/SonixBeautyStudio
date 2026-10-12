#include "LoginConfig.h"

namespace Private
{
    static constexpr const char* LoginSeverPath{":/config/settings/loginServer.ini"};
}  // namespace Private

LoginConfig* LoginConfig::instance(QObject* _parent) noexcept
{
    static LoginConfig* loginConfig{new LoginConfig{Private::LoginSeverPath, QSettings::IniFormat, _parent}};
    return loginConfig;
}

LoginConfig::LoginConfig(const QString& _fileName, QSettings::Format _format, QObject* _parent) : ConfigSetting{_fileName, _format, _parent}
{
    ConfigSetting::init();
}
