_Pragma("once");
#include <QObject>

class QJniObject;

class AndroidSettings : public QObject
{
    Q_OBJECT
public:
    ~AndroidSettings() noexcept = default;

    static auto instance() noexcept -> AndroidSettings*;

private:
    explicit(true) AndroidSettings(QObject* _parent = nullptr);

    auto init() noexcept -> void;

public:
    auto setScreenBrightness(float _value) noexcept -> void;

private:
    QJniObject* m_settingObject{nullptr};
};
