_Pragma("once");
#include <QObject>
#include "QuickMacro.hpp"

class Patient : public QObject
{
    Q_OBJECT
    QUICK_PROPERTY(QString, m_patientID, patientID, patientID, setPatientID, patientIDChanged)
public:
    explicit(true) Patient(QObject* _parent = nullptr);

    ~Patient() noexcept = default;

Q_SIGNALS:
    void patientIDChanged();

private:
    QString m_patientID{};
};
