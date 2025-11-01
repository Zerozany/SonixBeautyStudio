import QtQuick
import SonixBeautyUI
import QtQuick.Layouts

Item {
    id: root
    property var deviceName: null

    readonly property int spacing: 5
    readonly property int margins: 10
    readonly property string buttonText: "连接"
    readonly property string buttonSource: "qrc:/view/resource/HomePageIcons/connect.png"
    readonly property string buttonSourcePressed: "qrc:/view/resource/HomePageIcons/connectPressed.png"
    readonly property string deviceImageSource: "qrc:/view/resource/HomePageIcons/ProbeDevice.png"
    readonly property var elementRadius: ThemeManager.currentTheme["elementRadius"]
    readonly property var probeDeviceColor: ThemeManager.currentTheme["probeDeviceColor"]

    Rectangle {
        anchors.fill: parent
        radius: root.elementRadius
        color: root.probeDeviceColor

        RowLayout {
            anchors.fill: parent
            anchors.margins: root.margins
            spacing: root.spacing

            ImageLabel {
                Layout.preferredHeight: (root.height - (root.margins * 2)) * 0.65
                Layout.preferredWidth: implicitWidth
                text: root.deviceName
                source: root.deviceImageSource
                fontBold: true
                Layout.alignment: Qt.AlignVCenter
            }

            Item {
                Layout.fillWidth: true
            }

            SButton {
                text: qsTr(root.buttonText)
                Layout.preferredWidth: root.width * 0.1
                Layout.preferredHeight: (root.height - (root.margins * 2)) * 0.6
                layout: Qt.Vertical
                fontBold: false
                source: root.buttonSource
                sourcePressed: root.buttonSourcePressed
                Layout.alignment: Qt.AlignVCenter
            }
        }
    }
}
