_Pragma("once");
#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <string>
#include "HttpsManager.hpp"
#include "QuickMacro.hpp"

class QJSEngine;
class QQmlEngine;

class LoginManager final : public QObject, HttpsManager<const std::string&, int>
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT
    QUICK_PROPERTY(int, m_status, status, status, setStatus, statusChanged)
public:
    static LoginManager* create(QQmlEngine* _qmlEngine = nullptr, QJSEngine* _qJSEngine = nullptr);

    ~LoginManager() noexcept override = default;

    Q_DISABLE_COPY_MOVE(LoginManager)

public:
    Q_INVOKABLE void getCaptcha(const QString& _phoneNumbers);

private:
    explicit(true) LoginManager(const std::string& _host, int _port = 443, QObject* _parent = nullptr);

    void init(const std::string&, int&&) noexcept override;

    void connectSignal2Slot() noexcept;

Q_SIGNALS:
    void
    statusChanged();

private:
    httplib::Headers m_heads{{"User-Agent", "Mozilla/5.0"}, {"Accept", "application/json"}};
    int              m_status{};
};
