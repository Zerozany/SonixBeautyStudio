#include "LoginConfig.h"
#include <QFile>

LoginConfig::LoginConfig(const QString& _fileName, Format _format, QObject* _parent) : ConfigSetting{_fileName, _format, _parent}
{
    ConfigSetting::loadProperties();
}
