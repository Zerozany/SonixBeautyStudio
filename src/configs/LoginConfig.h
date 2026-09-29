_Pragma("once");
#include "ConfigSetting.h"
#include "QuickMacro.hpp"

class LoginConfig final : public ConfigSetting
{
    Q_OBJECT
    QUICK_PROPERTY(int, m_port, port, port, setPort, portChanged)
    QUICK_PROPERTY(QString, m_host, host, host, setHost, hostChanged)
    QUICK_PROPERTY(QString, m_captcha, captcha, captcha, setCaptcha, captchaChanged)
    QUICK_PROPERTY(QString, m_login, login, login, setLogin, loginChanged)
    QUICK_PROPERTY(QString, m_revise, revise, revise, setRevise, reviseChanged)
    QUICK_PROPERTY(QString, m_registration, registration, registration, setRgistration, registrationChanged)
    Q_CLASSINFO("port", "Server")
    Q_CLASSINFO("host", "Server")
    Q_CLASSINFO("captcha", "Path")
    Q_CLASSINFO("login", "Path")
    Q_CLASSINFO("revise", "Path")
    Q_CLASSINFO("registration", "Path")
public:
    static LoginConfig* instance(QObject* _parent = nullptr) noexcept;

    ~LoginConfig() noexcept override = default;

    Q_DISABLE_COPY_MOVE(LoginConfig)

private:
    explicit(true) LoginConfig(const QString& _fileName, QSettings::Format _format, QObject* _parent = nullptr);

Q_SIGNALS:
    void hostChanged();
    void portChanged();
    void captchaChanged();
    void loginChanged();
    void reviseChanged();
    void registrationChanged();

private:
    int     m_port{};
    QString m_host{};
    QString m_captcha{};
    QString m_login{};
    QString m_revise{};
    QString m_registration{};
};
