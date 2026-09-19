#include "LoginConfig.h"
#include <QFile>

namespace Private
{
    static constexpr const char*       LoginSeverPath{":/config/settings/loginServer.ini"};
    static constexpr QSettings::Format LoginSeverFormat{QSettings::IniFormat};
}  // namespace Private

LoginConfig* LoginConfig::instance(QObject* _parent) noexcept
{
    static LoginConfig* loginConfig{new LoginConfig{Private::LoginSeverPath, Private::LoginSeverFormat, _parent}};
    return loginConfig;
}

LoginConfig::LoginConfig(const QString& _fileName, QSettings::Format _format, QObject* _parent) : ConfigSetting{_fileName, _format, _parent}
{
    ConfigSetting::init();
}
