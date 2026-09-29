#include "LoginManager.h"
#include <QDir>
#include <QStandardPaths>
#include <QJSEngine>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonObject>
#include "LoginConfig.h"

LoginManager::LoginManager(const std::string& _host, int _port, QObject* _parent) : QObject{_parent}, HttpsManager<const std::string&, int>{_host, std::move(_port)}
{
    std::invoke(&LoginManager::init, this, _host, std::move(_port));
    std::invoke(&LoginManager::connectSignal2Slot, this);
}

LoginManager* LoginManager::create(QQmlEngine* _qmlEngine, QJSEngine* _qJSEngine)
{
    Q_UNUSED(_qJSEngine);
    static LoginManager* loginManager{new LoginManager{LoginConfig::instance()->host().toStdString(), LoginConfig::instance()->port(), qobject_cast<QQmlApplicationEngine*>(_qmlEngine)}};
    return loginManager;
}

bool LoginManager::getCaptcha(const QString& _phoneNumbers)
{
    httplib::Params captchaParams{{"phone", _phoneNumbers.toStdString()}, {"type", "1"}};
    auto            res = m_sslClient->Get(LoginConfig::instance()->captcha().toStdString(), captchaParams, this->m_heads);
    if (res && res->status == 200)
    {
        qDebug() << "响应:" << QString::fromStdString(res->body);
        qDebug() << "状态码:" << res->status;
        return true;
    }
    qDebug() << "失败，状态码:" << (res ? res->status : -1);
    return false;
}

bool LoginManager::login(const QString& _phoneNumbers, const QString& _password)
{
    QCryptographicHash hash{QCryptographicHash::Md5};
    hash.addData(_password.toUtf8());
    QJsonObject obj{};
    obj.insert("phone", _phoneNumbers);
    obj.insert("password", QString::fromStdString(hash.result().toHex().toLower().toStdString()));
    std::string body{QJsonDocument(obj).toJson(QJsonDocument::Compact).toStdString()};
    auto        res = m_sslClient->Post(LoginConfig::instance()->login().toStdString(), this->m_heads, body, "application/json");
    if (res && res->status == 200)
    {
        qDebug() << "响应:" << QString::fromStdString(res->body);
        qDebug() << "状态码:" << res->status;
        return true;
    }
    qDebug() << "失败，状态码:" << (res ? res->status : -1);
    return false;
}

bool LoginManager::revisePassword(const QString& _phoneNumbers, const QString& _password)
{
    QCryptographicHash hash{QCryptographicHash::Md5};
    hash.addData(_password.toUtf8());
    QJsonObject obj{};
    obj.insert("phone", _phoneNumbers);
    obj.insert("password", QString::fromStdString(hash.result().toHex().toLower().toStdString()));
    std::string body{QJsonDocument(obj).toJson(QJsonDocument::Compact).toStdString()};
    auto        res = m_sslClient->Post(LoginConfig::instance()->revise().toStdString(), this->m_heads, body, "application/json");
    if (res && res->status == 200)
    {
        qDebug() << "响应:" << QString::fromStdString(res->body);
        qDebug() << "状态码:" << res->status;
        return true;
    }
    qDebug() << "失败，状态码:" << (res ? res->status : -1);
    return false;
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

void LoginManager::connectSignal2Slot() noexcept
{
}
