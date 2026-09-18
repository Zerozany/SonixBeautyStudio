#include "LoginConfig.h"
#include <QFile>

LoginConfig* LoginConfig::instance(const QString& _fileName, QSettings::Format _format, QObject* _parent) noexcept
{
    static LoginConfig* loginConfig{new LoginConfig{_fileName, _format, _parent}};
    return loginConfig;
}

LoginConfig::LoginConfig(const QString& _fileName, QSettings::Format _format, QObject* _parent) : ConfigSetting{_fileName, _format, _parent}
{
    ConfigSetting::loadProperties();
}
