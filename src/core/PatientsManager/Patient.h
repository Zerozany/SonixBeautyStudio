_Pragma("once");
#include <QObject>
#include <QtQml>
#include "QuickMacro.hpp"
#include "BasicInformation.h"
#include "DataInformation.h"
#include "MediaInformation.h"

class Patient : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QUICK_CLASS_PROPERTY(BasicInformation*, m_basicInformation, basicInformation, basicInformation, setBasicInformation, basicInformationChanged)
    QUICK_CLASS_PROPERTY(DataInformation*, m_dataInformation, dataInformation, dataInformation, setDataInformation, dataInformationChanged)
    QUICK_CLASS_PROPERTY(MediaInformation*, m_mediaInformation, mediaInformation, mediaInformation, setMediaInformation, mediaInformationChanged)
public:
    explicit(true) Patient(QObject* _parent = nullptr);

    ~Patient() noexcept = default;

private:
    void init() noexcept;

Q_SIGNALS:
    void basicInformationChanged();
    void dataInformationChanged();
    void mediaInformationChanged();

private:
    BasicInformation* m_basicInformation{nullptr};
    DataInformation*  m_dataInformation{nullptr};
    MediaInformation* m_mediaInformation{nullptr};
};
