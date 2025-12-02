_Pragma("once");
#include <QObject>

class QJniObject;

class AndroidContext : public QObject
{
public:
    ~AndroidContext() noexcept = default;

    static auto instance() noexcept -> AndroidContext*;

    auto context() noexcept -> QJniObject*;

private:
    explicit(true) AndroidContext(QObject* _parent = nullptr);

private:
};
