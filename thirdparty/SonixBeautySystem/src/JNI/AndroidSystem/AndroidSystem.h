_Pragma("once");
#include <QObject>

class QJniObject;

class AndroidSystem : public QObject
{
    Q_OBJECT
public:
    ~AndroidSystem() noexcept = default;

    static auto instance() noexcept -> AndroidSystem*;

private:
    explicit(true) AndroidSystem(QObject* _parent = nullptr);

    auto init() noexcept -> void;

public:
    auto setScreenBrightness(float _value) noexcept -> void;

private:
    QJniObject* m_settingObject{nullptr};
};
