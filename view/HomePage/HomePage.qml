import QtQuick
import SonixBeautyUI

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

        ProbeDeviceList {
            id: probeDeviceList
            width: parent.width * (2 / 3)
            height: parent.height * 0.5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height * 0.04
        }

        Sidebar {
            id: sidebar
            width: 80
            height: parent.height * 0.4
            layout: sidebarLayout.Right
            anchors.verticalCenter: parent.verticalCenter
            imageButtonList: [
                {
                    text: "qrc:/view/resource/HomePageIcons/connect.png",
                    source: "qrc:/view/resource/HomePageIcons/connect.png",
                    sourcePressed: "qrc:/view/resource/HomePageIcons/connectPressed.png",
                    borderTag: true
                },
                {
                    text: "qr",
                    source: "qrc:/view/resource/HomePageIcons/connect.png",
                    sourcePressed: "qrc:/view/resource/HomePageIcons/connectPressed.png",
                    borderTag: true
                },
                {
                    text: "qrqrqrqr2",
                    source: "qrc:/view/resource/HomePageIcons/connect.png",
                    sourcePressed: "qrc:/view/resource/HomePageIcons/connectPressed.png",
                    borderTag: true
                },
            ]
        }
    }
}
