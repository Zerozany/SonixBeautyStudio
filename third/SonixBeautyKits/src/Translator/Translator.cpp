#include "Translator.h"
#include <QGuiApplication>
#include <QJSEngine>
#include <QQmlEngine>

Translator::Translator(QObject* _parent) : QObject{_parent}
{
}

Translator* Translator::create(QQmlEngine*, QJSEngine*)
{
    static Translator* translator{new Translator{}};
    return translator;
}

auto Translator::load(const QString& _languageQmPath) noexcept -> void
{
    qApp->removeTranslator(&m_translator);
    if (m_translator.load(_languageQmPath))
    {
        qApp->installTranslator(&m_translator);
    }
}
