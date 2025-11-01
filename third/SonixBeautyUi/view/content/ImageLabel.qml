import QtQuick
import SonixBeautyUI
import QtQuick.Layouts

Item {
    id: root
    property var text: null
    property var source: null
    property var fontBold: false

    readonly property int spacing: 0
    readonly property color labelColor: "transparent"
    readonly property color textColor: ThemeManager.currentTheme["textColor"]
    readonly property var elementRadius: ThemeManager.currentTheme["elementRadius"]
    // readonly property var textFontFamily: ThemeManager.fontFamily

    Rectangle {
        anchors.fill: parent
        radius: root.elementRadius
        color: root.labelColor

        RowLayout {
            anchors.fill: parent
            spacing: root.spacing

            Image {
                id: labelImage
                Layout.preferredWidth: Math.min(implicitWidth, root.width)
                Layout.preferredHeight: Math.min(implicitHeight, root.height)
                source: root.source
                fillMode: Image.PreserveAspectFit
                Layout.alignment: Qt.AlignVCenter
            }

            Text {
                id: labelText
                text: root.text
                Layout.preferredWidth: Math.min(contentWidth, root.width)
                Layout.preferredHeight: Math.min(contentHeight, root.height)
                color: root.textColor
                font.pixelSize: Math.floor(root.height * (1 / 2))
                font.bold: root.fontBold
                Layout.alignment: Qt.AlignVCenter
            }
        }
    }

    Component.onCompleted: {
        root.width = labelImage.implicitWidth + labelText.implicitWidth + root.spacing;
    }
}
