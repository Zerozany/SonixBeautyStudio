#include "ThemeManager.h"
#include <QJSEngine>
#include <QQmlEngine>
#include <QSettings>
#include <QStandardPaths>
#include <QDir>

Q_INVOKABLE QString ThemeManager::currentThemeName() const
{
    return m_currentThemeName;
}

Q_INVOKABLE void ThemeManager::setCurrentThemeName(const QString& _currentThemeName)
{
    if (m_currentThemeName == _currentThemeName)
    {
        return;
    }
    m_currentThemeName = _currentThemeName;
    Q_EMIT this->currentThemeNameChanged();
}

QVariantMap ThemeManager::currentTheme() const
{
    return m_currentTheme;
}

void ThemeManager::setCurrentTheme(const QVariantMap& _currentTheme)
{
    if (m_currentTheme == _currentTheme)
    {
        return;
    }
    m_currentTheme = _currentTheme;
    Q_EMIT this->currentThemeChanged();
}

QVariantMap ThemeManager::fontSize() const
{
    return m_fontSize;
}

void ThemeManager::setFontSize(const QVariantMap& _fontSize)
{
    if (m_fontSize == _fontSize)
    {
        return;
    }
    m_fontSize = _fontSize;
    Q_EMIT this->fontSizeChanged();
}

QVariantMap ThemeManager::styleSize() const
{
    return m_styleSize;
}

void ThemeManager::setStyleSize(const QVariantMap& _styleSize)
{
    if (m_styleSize == _styleSize)
    {
        return;
    }
    m_styleSize = _styleSize;
    Q_EMIT this->styleSizeChanged();
}

ThemeManager* ThemeManager::create(QQmlEngine*, QJSEngine*)
{
    static ThemeManager* themeManager{new ThemeManager{}};
    return themeManager;
}

ThemeManager::ThemeManager(QObject* _parent) : QObject{_parent}
{
    std::invoke(&ThemeManager::connectSignal2Slot, this);
    std::invoke(&ThemeManager::init, this);
}

auto ThemeManager::init() noexcept -> void
{
    m_settings = new QSettings{QDir{QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)}.filePath("config/settings.ini"), QSettings::IniFormat, this};
    // qDebug() << m_settings->fileName();
    m_settings->beginGroup("Themes");
    if ((m_settings->contains("ThemeName") && !m_settings->value("ThemeName").isNull()) || !m_settings->contains("ThemeName"))
    {
        m_settings->setValue("ThemeName", "lightTheme");
        this->setCurrentThemeName("lightTheme");
    }
    m_settings->endGroup();
    this->setFontSize(Themes::fontSize);
    this->setStyleSize(Themes::styleSize);
}

auto ThemeManager::connectSignal2Slot() noexcept -> void
{
    connect(this, &ThemeManager::currentThemeNameChanged, this, &ThemeManager::onCurrentThemeNameChanged);
}

void ThemeManager::onCurrentThemeNameChanged()
{
    if (m_currentThemeName == "lightTheme")
    {
        this->setCurrentTheme(Themes::lightTheme);
    }
}
