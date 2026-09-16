#include "LoginManager.h"
#include <QDir>
#include <QStandardPaths>

LoginManager::LoginManager(const std::string& _host, int _port, QObject* _parent) : QObject{_parent}, HttpsManager<const std::string&, int>{_host, std::move(_port)}
{
    std::invoke(&LoginManager::init, this, _host, std::move(_port));
}

void LoginManager::getCaptcha()
{
    httplib::Headers headers = {
        {"User-Agent", "Mozilla/5.0"},
        {"Accept", "application/json"}};

    auto res = m_sslClient->Get("/app/V0/phoneCode?phone=18294821095&type=1", headers);

    if (res && res->status == 200)
    {
        qDebug() << "响应:" << QString::fromStdString(res->body);
        qDebug() << "状态码:" << res->status;
    }
    else
    {
        qDebug() << "失败，状态码:" << (res ? res->status : -1);
    }
}

void LoginManager::init(const std::string& _host, int&& _port) noexcept
{
    Q_UNUSED(_host)
    Q_UNUSED(_port)
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
