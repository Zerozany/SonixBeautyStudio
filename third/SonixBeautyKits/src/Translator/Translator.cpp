#include "Translator.h"
#include <QGuiApplication>

Translator::Translator(QObject* _parent) : QObject{_parent}
{
}

auto Translator::instance() noexcept -> Translator&
{
    static Translator translator{};
    return translator;
}

auto Translator::load(const QString& _languageQmPath) noexcept -> void
{
    if (!qApp->removeTranslator(&m_translator))
    {
        return;
    }
    if (m_translator.load(_languageQmPath))
    {
        qApp->installTranslator(&m_translator);
    }
}
