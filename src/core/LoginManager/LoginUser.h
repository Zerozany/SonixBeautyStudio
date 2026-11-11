_Pragma("once");
#include <QObject>
#include <QtQml/qqmlregistration.h>
#include "QuickMacro.hpp"

class LoginUser : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QUICK_PROPERTY(QString, m_userPhone, userPhone, userPhone, setUserPhone, userPhoneChanged)
    QUICK_PROPERTY(QString, m_userPassword, userPassword, userPassword, setUserPassword, userPasswordChanged)
    QUICK_PROPERTY(QString, m_userDepartment, userDepartment, userDepartment, setUserDepartment, userDepartmentChanged)
    QUICK_PROPERTY(QString, m_userHospital, userHospital, userHospital, setUserHospital, userHospitalChanged)
    QUICK_PROPERTY(QString, m_userNickname, userNickname, userNickname, setUserNickname, userNicknameChanged)
public:
    explicit(true) LoginUser(QObject* _parent = nullptr);

    ~LoginUser() noexcept = default;

Q_SIGNALS:
    void userPhoneChanged();
    void userPasswordChanged();
    void userDepartmentChanged();
    void userHospitalChanged();
    void userNicknameChanged();

private:
    QString m_userPhone{};
    QString m_userPassword{};
    QString m_userDepartment{};
    QString m_userHospital{};
    QString m_userNickname{};
};
