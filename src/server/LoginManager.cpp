#include "LoginManager.h"
#include <QDir>
#include <QStandardPaths>
#include <QJSEngine>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include "LoginConfig.h"

LoginManager::LoginManager(const std::string& _host, int _port, QObject* _parent) : QObject{_parent}, HttpsManager<const std::string&, int>{_host, std::move(_port)}
{
    std::invoke(&LoginManager::init, this, _host, std::move(_port));
}

LoginManager* LoginManager::create(QQmlEngine* _qmlEngine, QJSEngine* _qJSEngine)
{
    Q_UNUSED(_qJSEngine);
    static LoginManager* loginManager{new LoginManager{LoginConfig::instance()->host().toStdString(), LoginConfig::instance()->port(), qobject_cast<QQmlApplicationEngine*>(_qmlEngine)}};
    return loginManager;
}

void LoginManager::getCaptcha(const QString& _phoneNumbers)
{
    httplib::Params captchaParams{{"phone", _phoneNumbers.toStdString()}, {"type", "1"}};
    auto            res = m_sslClient->Get(LoginConfig::instance()->captcha().toStdString(), captchaParams, this->m_heads);
    if (res && res->status == 200)
    {
        qDebug() << "响应:" << QString::fromStdString(res->body);
        qDebug() << "状态码:" << res->status;
        return;
    }
    qDebug() << "失败，状态码:" << (res ? res->status : -1);
}

void LoginManager::init(const std::string&, int&&) noexcept
{
    const QString cacertPath{QDir{QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)}.filePath("cacert.pem")};
    if (!QFile::exists(cacertPath))
    {
        if (!QFile::copy(":/config/Android/cacert.pem", cacertPath))
        {
            qDebug() << "CA 复制失败";
            return;
        }
        QFile::setPermissions(cacertPath, QFile::ReadOwner | QFile::WriteOwner);
    }
    qDebug() << "CA exists:" << QFile::exists(cacertPath) << cacertPath;
    m_sslClient->set_ca_cert_path(cacertPath.toStdString().c_str());
}
