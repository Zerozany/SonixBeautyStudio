#include "Translator.h"
#include <QGuiApplication>
#include <QJSEngine>
#include <QQmlEngine>

Translator::Translator(QObject* _parent) : QObject{_parent}
{
    std::invoke(&Translator::connectSignal2Slot, this);
}

auto Translator::connectSignal2Slot() noexcept -> void
{
    connect(this, &Translator::languageChanged, this, &Translator::onLanguageChanged, Qt::AutoConnection);
}

void Translator::onLanguageChanged()
{
    qApp->removeTranslator(&m_translator);
    if (m_translator.load(m_language))
    {
        qApp->installTranslator(&m_translator);
    }
}

Translator* Translator::create(QQmlEngine*, QJSEngine*)
{
    static Translator* translator{new Translator{}};
    return translator;
}

QString Translator::language() const
{
    return m_language;
}

void Translator::setLanguage(const QString& _language)
{
    if (m_language == _language)
    {
        return;
    }
    m_language = _language;
    Q_EMIT this->languageChanged();
}
