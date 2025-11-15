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
    };

    inline QVariantMap fontFamilys{
        {"zh_CW", "微软雅黑"},
        {"en_US", "Arial"},
    };

}  // namespace Themes
