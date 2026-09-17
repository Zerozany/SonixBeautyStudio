_Pragma("once");
#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <string>
#include "HttpsManager.hpp"
// #include "QuickMacro.hpp"

class QJSEngine;
class QQmlEngine;

class LoginManager final : public QObject, HttpsManager<const std::string&, int>
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT
    Q_PROPERTY(QString host READ host CONSTANT)
    Q_PROPERTY(int port READ port CONSTANT)
public:
    static LoginManager* create(QQmlEngine* _qmlEngine = nullptr, QJSEngine* _qJSEngine = nullptr);

    ~LoginManager() noexcept override = default;

    Q_DISABLE_COPY_MOVE(LoginManager)

public:
    QString host() { return m_host; }
    int     port() { return m_port; }

public:
    Q_INVOKABLE void getCaptcha();

private:
    explicit(true) LoginManager(const std::string& _host, int _port = 443, QObject* _parent = nullptr);

    void init(const std::string&, int&&) noexcept override;

Q_SIGNALS:

private:
    QString m_host{};
    int     m_port{};
};
