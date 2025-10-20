import QtQuick
import SonixBeautyUi
import QtQuick.Controls

Item {
    id: root

    readonly property int spacing: 5
    readonly property int margins: 5
    readonly property int borderWidth: 0
    readonly property int titleHeight: 40
    readonly property string titleName: "设备列表"
    readonly property string titleSource: "qrc:/view/resource/HomePageIcons/DeviceList.png"
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
                id: titleRow
                width: parent.width
                height: root.titleHeight
                anchors.leftMargin: root.margins

                ImageLabel {
                    height: parent.height
                    text: qsTr(root.titleName)
                    source: root.titleSource
                }
            }

            Flickable {
                width: parent.width
                height: parent.height - titleRow.height - root.spacing
                contentWidth: width
                contentHeight: column.height
                clip: true

                Column {
                    id: column
                    width: parent.width
                    spacing: root.spacing

                    ProbeDevice {
                        width: parent.width
                        height: 70
                        deviceName: "US06-9C50D101E37E"
                    }

                    ProbeDevice {
                        width: parent.width
                        height: 70
                        deviceName: "US07-9C50D101E37E"
                    }

                    ProbeDevice {
                        width: parent.width
                        height: 70
                        deviceName: "US08-9C50D101E37E"
                    }

                    ProbeDevice {
                        width: parent.width
                        height: 70
                        deviceName: "US09-9C50D101E37E"
                    }

                    ProbeDevice {
                        width: parent.width
                        height: 70
                        deviceName: "US10-9C50D101E37E"
                    }

                    ProbeDevice {
                        width: parent.width
                        height: 70
                        deviceName: "US10-9C50D101E37E"
                    }

                    ProbeDevice {
                        width: parent.width
                        height: 70
                        deviceName: "US10-9C50D101E37E"
                    }

                    ProbeDevice {
                        width: parent.width
                        height: 70
                        deviceName: "US10-9C50D101E37E"
                    }
                }
            }
        }
    }
}
