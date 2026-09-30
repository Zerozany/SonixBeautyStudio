import QtQuick
// import QtQuick.Controls
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

    Row {
        width: parent.width * 0.2
        height: parent.height * 0.05
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
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
