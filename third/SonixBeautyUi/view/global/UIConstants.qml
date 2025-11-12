pragma Singleton
import QtQuick
import SonixBeautyUI

QtObject {
    readonly property int margins: Math.round(5 * Screen.devicePixelRatio)
    readonly property int elementRadius: ThemeManager.currentTheme.elementRadius
    readonly property color elementColor: Qt.color(ThemeManager.currentTheme.elementColor)
    readonly property color textColor: Qt.color(ThemeManager.currentTheme.textColor)
}
