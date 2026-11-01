_Pragma("once");
#include <QObject>
#include <QtQml>
#include "QuickMacro.hpp"

class BasicInformation : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("BasicInformation is managed by Patient")
    QUICK_ONLYR_PROPERTY(QString, m_patientID, patientID, patientID)
    QUICK_ONLYR_PROPERTY(QString, m_startTime, startTime, startTime)
public:
    explicit(true) BasicInformation(QObject* _parent = nullptr);

    ~BasicInformation() noexcept = default;

private:
    void init() noexcept;

private:
    QString m_patientID{};
    QString m_startTime{};
};
