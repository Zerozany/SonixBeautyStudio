_Pragma("once");
#include <QObject>

class ThirdManager : public QObject
{
    Q_OBJECT
public:
    static auto instance(QObject* _parent = nullptr) noexcept -> ThirdManager*;

    ~ThirdManager() noexcept = default;

    Q_DISABLE_COPY_MOVE(ThirdManager)
public:
    auto init() noexcept -> void;

private:
    explicit(true) ThirdManager(QObject* _parent = nullptr);
};
