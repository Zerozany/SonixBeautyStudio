_Pragma("once");
#include <QObject>
#include <QtQml>
#include "QuickMacro.hpp"
#include "Patient.h"

class PatientsManager : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT
public:
    static PatientsManager* create(QQmlEngine* _qmlEngine = nullptr, QJSEngine* _qJSEngine = nullptr);

    virtual ~PatientsManager() noexcept override = default;

    Q_DISABLE_COPY_MOVE(PatientsManager)

private:
    explicit(true) PatientsManager(QObject* _parent = nullptr);

public:
    Q_INVOKABLE virtual void createPatient() noexcept;

    Q_INVOKABLE virtual bool deletePatient() noexcept;

    Q_INVOKABLE virtual void savePatient(Patient* _patient) noexcept;

    Q_INVOKABLE virtual QVariantList queryPatient(const QString& _patientField);
};
