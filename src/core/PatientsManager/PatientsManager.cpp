#include "PatientsManager.h"

PatientsManager* PatientsManager::create(QQmlEngine* _qmlEngine, QJSEngine* _qJSEngine)
{
    static PatientsManager* patientsManager{new PatientsManager{_qmlEngine}};
    return patientsManager;
}

PatientsManager::PatientsManager(QObject* _parent) : ClassesManager{_parent}
{
}
