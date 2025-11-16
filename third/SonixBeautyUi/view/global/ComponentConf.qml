pragma Singleton
import QtQuick
import SonixBeautyUI

QtObject {

    readonly property var appSizeTable: {
        "elementMargins": Math.round(5 * Screen.devicePixelRatio),
        "elementRadius": Math.round(5 * Screen.devicePixelRatio),
        "elementSpacing": Math.round(5 * Screen.devicePixelRatio)
    }

    readonly property var appColorTable: {
        "backgroundColor": ThemeManager.currentTheme.backgroundColor,
        "elementColor": ThemeManager.currentTheme.elementColor,
        "textColor": ThemeManager.currentTheme.textColor,
        "textColorPressed": ThemeManager.currentTheme.textColorPressed
    }

    readonly property var pointSizeTable: {
        "XXL": 16,
        "XL": 14,
        "L": 12,
        "S": 10,
        "M": 8
    }
}
