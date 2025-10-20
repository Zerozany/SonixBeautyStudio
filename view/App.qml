import QtQuick
import SonixBeautyUi
import "HomePage"

Item {
    id: root

    property var backgroundColor: null

    readonly property int appTopMargin: 25
    readonly property int appbottomMargin: 15

    Rectangle {
        anchors.fill: parent
        anchors.topMargin: root.appTopMargin
        anchors.bottomMargin: root.appbottomMargin
        color: root.backgroundColor

        HomePage {
            id: homePage
            width: parent.width * (2 / 3)
            height: parent.height * 0.5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height * 0.04
        }
    }
}
