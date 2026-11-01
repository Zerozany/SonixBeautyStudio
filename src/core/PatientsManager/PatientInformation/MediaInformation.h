_Pragma("once");
#include <QObject>

class MediaInformation : public QObject
{
    Q_OBJECT
public:
    explicit(true) MediaInformation(QObject* _parent = nullptr);

    ~MediaInformation() noexcept = default;
};
