_Pragma("once");
#include <QObject>

class DataInformation : public QObject
{
    Q_OBJECT
public:
    explicit(true) DataInformation(QObject* _parent = nullptr);

    ~DataInformation() noexcept = default;
};
