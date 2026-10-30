_Pragma("once");
#include <QObject>

class BasicInformation
{
private:
    /* data */
public:
    explicit(true) BasicInformation(QObject* _parent = nullptr);

    ~BasicInformation() noexcept = default;
};
