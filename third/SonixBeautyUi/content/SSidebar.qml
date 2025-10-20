import QtQuick
import SonixBeautyUi

// import QtQuick.Layouts

Item {
    id: root

    readonly property var elementRadius: ThemeManager.currentTheme["elementRadius"]
    readonly property var sidebarColor: ThemeManager.currentTheme["elementColor"]

    Rectangle {
        anchors.fill: parent
        radius: root.elementRadius
        color: root.sidebarColor
    }
}
