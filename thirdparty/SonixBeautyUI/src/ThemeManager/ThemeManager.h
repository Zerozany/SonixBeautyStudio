_Pragma("once");
#include <QObject>
#include <QtQml>
#include <QVariantMap>
#include "Themes.hpp"

#if defined(Q_OS_WINDOWS) && defined(_MSC_VER)
#    ifndef SONIXEX_API
#        ifdef SONIXEXPROTS
#            define SONIXEX_API Q_DECL_EXPORT
#        else
#            define SONIXEX_API Q_DECL_IMPORT
#        endif
#    endif
#else
#    ifndef SONIXEX_API
#        define SONIXEX_API
#    endif
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
    Q_PROPERTY(QVariantMap fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged);
    Q_PROPERTY(QVariantMap styleSize READ styleSize WRITE setStyleSize NOTIFY styleSizeChanged);

public:
    ~ThemeManager() noexcept = default;

    Q_INVOKABLE QString currentThemeName() const;
    Q_INVOKABLE void    setCurrentThemeName(const QString& _currentThemeName);

    Q_INVOKABLE QVariantMap currentTheme() const;
    Q_INVOKABLE void        setCurrentTheme(const QVariantMap& _currentTheme);

    Q_INVOKABLE QVariantMap fontSize() const;
    Q_INVOKABLE void        setFontSize(const QVariantMap& _fontSize);

    Q_INVOKABLE QVariantMap styleSize() const;
    Q_INVOKABLE void        setStyleSize(const QVariantMap& _styleSize);

public:
    static ThemeManager* create(QQmlEngine*, QJSEngine*);

private:
    explicit(true) ThemeManager(QObject* _parent = nullptr);

    auto init() noexcept -> void;

    auto connectSignal2Slot() noexcept -> void;

Q_SIGNALS:
    void currentThemeNameChanged();

    void currentThemeChanged();

    void fontSizeChanged();

    void styleSizeChanged();

private Q_SLOTS:
    void onCurrentThemeNameChanged();

private:
    QSettings*  m_settings{nullptr};
    QString     m_currentThemeName{};
    QVariantMap m_currentTheme{};
    QVariantMap m_fontSize{};
    QVariantMap m_styleSize{};
};
