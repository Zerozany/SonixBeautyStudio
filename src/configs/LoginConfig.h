_Pragma("once");
#include "ConfigSetting.h"
#include "QuickMacro.hpp"

class LoginConfig final : public ConfigSetting
{
    Q_OBJECT
    QUICK_PROPERTY(QString, m_host, host, host, setHost, hostChanged)
    QUICK_PROPERTY(int, m_port, port, port, setPort, portChanged)
    QUICK_PROPERTY(QString, m_captcha, captcha, captcha, setCaptcha, captchaChanged)
    Q_CLASSINFO("host", "Server")
    Q_CLASSINFO("port", "Server")
    Q_CLASSINFO("captcha", "Path")
public:
    explicit(true) LoginConfig(const QString& _fileName, Format _format, QObject* _parent = nullptr);

    ~LoginConfig() noexcept override = default;

Q_SIGNALS:
    void hostChanged();
    void portChanged();
    void captchaChanged();

private:
    QString m_host{};
    int     m_port{};
    QString m_captcha{};
};
