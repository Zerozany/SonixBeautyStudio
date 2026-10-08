import QtQuick
import QtQuick.Layouts
import QZeroMaterialUI

Item {
    id: root

    StackLayout {
        id: stackLayout
        width: parent.width
        height: parent.height * 0.95
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        currentIndex: 0

        WifiPage {}

        LoginPage {}
    }

    MaterialSeparator {
        id: sparator
        width: parent.width
        orientation: Qt.Horizontal
        anchors.top: stackLayout.bottom
    }

    Row {
        width: parent.width * 0.2
        height: parent.height * 0.03
        anchors.top: sparator.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 20

        MaterialButton {
            text: "Wifi相关"
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                stackLayout.currentIndex = 0;
            }
        }
        MaterialButton {
            text: "用户相关"
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                stackLayout.currentIndex = 1;
            }
        }
    }
}
