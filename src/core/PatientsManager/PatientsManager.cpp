#include "PatientsManager.h"

PatientsManager* PatientsManager::create(QQmlEngine* _qmlEngine, QJSEngine* _qJSEngine)
{
    Q_UNUSED(_qJSEngine)
    static PatientsManager* patientsManager{new PatientsManager{_qmlEngine}};
    return patientsManager;
}

PatientsManager::PatientsManager(QObject* _parent) : QObject{_parent}
{
}

void PatientsManager::createPatient() noexcept
{
}

bool PatientsManager::deletePatient() noexcept
{
    return bool{};
}

void PatientsManager::savePatient(Patient* _patient) noexcept
{
    Q_UNUSED(_patient)
}

QVariantList PatientsManager::queryPatient(const QString& _patientField)
{
    Q_UNUSED(_patientField)
    return QVariantList{};
}
