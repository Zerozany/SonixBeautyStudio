_Pragma("once");
#include <QVariantMap>
#include <QColor>

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
        {"labelColor", {"transparent"}},
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
        {"elementMargins", 5},
        {"elementRadius", 5},
        {"elementSpacing", 5},
    };

}  // namespace Themes
