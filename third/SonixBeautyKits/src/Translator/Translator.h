_Pragma("once");
#include <QObject>
#include <QTranslator>
#include <QtQml/qqmlregistration.h>

class Translator : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    ~Translator() noexcept = default;

public:
    static auto instance() noexcept -> Translator&;

    auto load(const QString& _languageQmPath) noexcept -> void;

private:
    explicit(true) Translator(QObject* _parent = nullptr);

private:
    QTranslator m_translator{};
};
