import QtQuick
import SonixBeautyUi
import QtQuick.Controls

Item {
    id: root

    readonly property int spacing: 5
    readonly property int margins: 5
    readonly property int borderWidth: 0
    readonly property var elementRadius: ThemeManager.currentTheme["elementRadius"]
    readonly property var elementColor: ThemeManager.currentTheme["elementColor"]
    readonly property var borderColor: ThemeManager.currentTheme["borderColor"]

    Rectangle {
        anchors.fill: parent
        radius: root.elementRadius
        color: root.elementColor
        border.color: root.borderColor
        border.width: root.borderWidth

        Column {
            anchors.fill: parent
            anchors.margins: root.margins
            spacing: root.spacing

            Row {
                width: parent.width
                height: 40
                anchors.leftMargin: 5

                ImageLabel {
                    height: parent.height
                    text: qsTr("设备列表")
                    source: "qrc:/view/resource/HomePageIcons/DeviceList.png"
                }
            }

            ScrollView {
                width: parent.width
                height: parent.height - 40
                clip: true
                ScrollBar.vertical.policy: ScrollBar.AlwaysOff
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

                Column {
                    anchors.fill: parent
                    spacing: root.spacing

                    ProbeDevice {
                        width: parent.width
                        height: 80
                        deviceName: "US06-9C50D101E37E"
                    }

                    ProbeDevice {
                        width: parent.width
                        height: 80
                        deviceName: "US07-9C50D101E37E"
                    }

                    ProbeDevice {
                        width: parent.width
                        height: 80
                        deviceName: "US08-9C50D101E37E"
                    }

                    ProbeDevice {
                        width: parent.width
                        height: 80
                        deviceName: "US09-9C50D101E37E"
                    }

                    ProbeDevice {
                        width: parent.width
                        height: 80
                        deviceName: "US10-9C50D101E37E"
                    }

                    ProbeDevice {
                        width: parent.width
                        height: 80
                        deviceName: "US10-9C50D101E37E"
                    }

                    ProbeDevice {
                        width: parent.width
                        height: 80
                        deviceName: "US10-9C50D101E37E"
                    }

                    ProbeDevice {
                        width: parent.width
                        height: 80
                        deviceName: "US10-9C50D101E37E"
                    }
                }
            }
        }
    }
}
