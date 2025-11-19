_Pragma("once");
#include <QVariantMap>
#include <QColor>
#include <QScreen>

namespace Themes
{
    inline QVariantMap lightTheme{
        {"backgroundColor", {"#f0efee"}},
        {"textColor", {"#0e0d0d"}},
        {"textColorPressed", {"#cdcdcd"}},
        {"buttonColor", {"#FFFFFF"}},
        {"elementColor", {"#FFFFFF"}},
        {"borderColor", {"#cdcdcd"}},
        {"probeDeviceColor", {"#66e1e1"}},
    };

    inline QVariantMap fontFamilys{
        {"zh_CW", "微软雅黑"},
        {"en_US", "Arial"},
    };

    inline QVariantMap fontSize{
        {"XXL", 16},
        {"XL", 14},
        {"L", 12},
        {"S", 10},
        {"M", 8},
    };

    inline QVariantMap styleSize{
        {"elementMargins", 5 * QGuiApplication::primaryScreen()->devicePixelRatio()},
        {"elementRadius", 5 * QGuiApplication::primaryScreen()->devicePixelRatio()},
        {"elementSpacing", 5 * QGuiApplication::primaryScreen()->devicePixelRatio()},
    };

}  // namespace Themes
