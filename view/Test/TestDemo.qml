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

        Rectangle {
            color: "red"
        }

        Rectangle {
            color: "blue"
        }

        Rectangle {
            color: "pink"
        }

        Rectangle {
            color: '#aff023'
        }
    }

    MaterialSeparator {
        id: sparator
        width: parent.width
        orientation: Qt.Horizontal
        anchors.top: stackLayout.bottom
    }

    Row {
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

        MaterialButton {
            text: "Linux"
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                stackLayout.currentIndex = 2;
            }
        }

        MaterialButton {
            text: "Config"
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                stackLayout.currentIndex = 3;
            }
        }

        MaterialButton {
            text: "Log"
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                stackLayout.currentIndex = 4;
            }
        }

        MaterialButton {
            text: "Setting"
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                stackLayout.currentIndex = 5;
            }
        }
    }
}
