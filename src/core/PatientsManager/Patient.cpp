#include "Patient.h"

Patient::Patient(QObject* _parent) : QObject{_parent}
{
    std::invoke(&Patient::init, this);
}

void Patient::init() noexcept
{
    this->setBasicInformation(new BasicInformation{this});
    this->setDataInformation(new DataInformation{this});
    this->setMediaInformation(new MediaInformation{this});
}
