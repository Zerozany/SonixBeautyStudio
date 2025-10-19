import QtQuick
import SonixBeautyUi
import "HomePage"

Rectangle {
    id: root
    anchors.fill: parent

    color: ThemeManager.currentTheme["backgroundColor"]

    HomePage {
        id: homePage
        width: root.width * (2 / 3)
        height: root.height * (1 / 2)
        anchors.horizontalCenter: root.horizontalCenter
        anchors.bottom: root.bottom
        anchors.bottomMargin: root.height * 0.05
    }
}
