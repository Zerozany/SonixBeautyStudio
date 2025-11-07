_Pragma("once");
#include <QObject>
#include <QTranslator>
#include <QtQml/qqmlregistration.h>

class QJSEngine;
class QQmlEngine;

class Translator : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT
public:
    ~Translator() noexcept = default;

public:
    static Translator* create(QQmlEngine*, QJSEngine*);

    auto load(const QString& _languageQmPath) noexcept -> void;

private:
    explicit(true) Translator(QObject* _parent = nullptr);

private:
    QTranslator m_translator{};
};
