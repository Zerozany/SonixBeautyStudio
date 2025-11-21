import QtQuick
import QtQuick.Layouts

Rectangle {
    id: root
    radius: root.elementRadius
    color: root.labelColor

    property string text: ""
    property url source: ""
    property bool fontBold: false

    readonly property string textColor: ThemeManager.currentTheme["textColor"]
    readonly property string labelColor: ThemeManager.currentTheme["labelColor"]
    readonly property int elementRadius: ThemeManager.styleSize["elementRadius"]
    readonly property int elementMargins: ThemeManager.styleSize["elementMargins"]
    readonly property int elementSpacing: ThemeManager.styleSize["elementSpacing"]

    RowLayout {
        anchors.centerIn: parent
        spacing: root.width <= root.height ? root.elementSpacing * 0.2 : root.elementSpacing * 1.0

        Image {
            source: root.source
            fillMode: Image.PreserveAspectFit
            Layout.preferredWidth: root.width <= root.height ? root.width * 0.2 : root.height * 0.5
            Layout.alignment: Qt.AlignVCenter
        }

        Text {
            text: root.text
            color: root.textColor
            wrapMode: Text.WordWrap
            font.pixelSize: root.width <= root.height ? Math.floor(root.width * 0.3) : Math.floor(root.height * 0.45)
            font.bold: root.fontBold
            verticalAlignment: Text.AlignVCenter
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
        }
    }
}
