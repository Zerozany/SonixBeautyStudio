_Pragma("once");
#include <QObject>
#include <QtQml>
#include <QVariantMap>
#include "Themes.hpp"

#if defined(Q_OS_WINDOWS) && defined(_MSC_VER)
#ifdef SONIXEXPROTS
#define SONIXEX_API Q_DECL_EXPORT
#else
#define SONIXEX_API Q_DECL_IMPORT
#endif
#else
#define SONIXEX_API
#endif

class QJSEngine;
class QQmlEngine;
class QSettings;

class SONIXEX_API ThemeManager : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT
    Q_PROPERTY(QString currentThemeName READ currentThemeName WRITE setCurrentThemeName NOTIFY currentThemeNameChanged);
    Q_PROPERTY(QVariantMap currentTheme READ currentTheme WRITE setCurrentTheme NOTIFY currentThemeChanged);

public:
    ~ThemeManager() noexcept = default;

    Q_INVOKABLE QString currentThemeName() const;
    Q_INVOKABLE void    setCurrentThemeName(const QString& _currentThemeName);

    Q_INVOKABLE QVariantMap currentTheme() const;
    Q_INVOKABLE void        setCurrentTheme(const QVariantMap& _currentTheme);

public:
    static ThemeManager* create(QQmlEngine*, QJSEngine*);

private:
    explicit(true) ThemeManager(QObject* _parent = nullptr);

    auto init() noexcept -> void;

    auto connectSignal2Slot() noexcept -> void;

Q_SIGNALS:
    void currentThemeChanged();

    void fontFamilyChanged();

    void currentThemeNameChanged();

private Q_SLOTS:
    void onCurrentThemeNameChanged();

private:
    QString     m_currentThemeName{};
    QVariantMap m_currentTheme{};
    QSettings*  m_settings{nullptr};
};
