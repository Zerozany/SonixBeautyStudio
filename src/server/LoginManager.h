_Pragma("once");
#include <QObject>
#include <string>
#include "HttpsManager.hpp"

class LoginManager final : public QObject, HttpsManager<const std::string&, int>
{
    Q_OBJECT

public:
    explicit(true) LoginManager(const std::string& _host, int _port = 443, QObject* _parent = nullptr);

    ~LoginManager() noexcept override = default;

public:
    void getCaptcha();

private:
    void init(const std::string& _host, int&& _port) noexcept override;
};
