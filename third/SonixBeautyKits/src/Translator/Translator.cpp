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
    qApp->removeTranslator(&m_translator);
    // 加载新翻译文件
    if (m_translator.load(_languageQmPath))
    {
        qApp->installTranslator(&m_translator);
    }
}
