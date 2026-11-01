#include "BasicInformation.h"
#include <QDateTime>

BasicInformation::BasicInformation(QObject* _parent) : QObject{_parent}
{
    std::invoke(&BasicInformation::init, this);
}

void BasicInformation::init() noexcept
{
    QDateTime currentTime{QDateTime::currentDateTime()};
    this->m_patientID = currentTime.toString("yyyyMMddHHmmss");
    this->m_startTime = currentTime.toString("yyyy-MM-dd HH:mm:ss");
}
