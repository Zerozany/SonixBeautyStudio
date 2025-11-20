_Pragma("once");
#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QTranslator>

class QJSEngine;
class QQmlEngine;

class Translator : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)
public:
    ~Translator() noexcept = default;

public:
    static Translator* create(QQmlEngine*, QJSEngine*);

    Q_INVOKABLE QString language() const;
    Q_INVOKABLE void    setLanguage(const QString& _language);

private:
    explicit(true) Translator(QObject* _parent = nullptr);

    auto connectSignal2Slot() noexcept -> void;

Q_SIGNALS:
    void languageChanged();

private Q_SLOTS:
    void onLanguageChanged();

private:
    QTranslator m_translator{};
    QString     m_language{};
};
