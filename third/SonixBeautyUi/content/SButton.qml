import QtQuick
import SonixBeautyUi
import QtQuick.Layouts

Item {
    id: root
    property var text: null
    property var source: null
    property var sourcePressed: null
    property var fontBold: false
    property var layout: Qt.Horizontal

    readonly property int spacing: 2
    readonly property color textColor: ThemeManager.currentTheme["textColor"]
    readonly property color buttonColor: ThemeManager.currentTheme["buttonColor"]
    readonly property var elementRadius: ThemeManager.currentTheme["elementRadius"]
    readonly property var textColorPressed: ThemeManager.currentTheme["textColorPressed"]
    // readonly property var textFontFamily: ThemeManager.fontFamily

    signal clicked

    Rectangle {
        id: rectangle
        anchors.fill: parent
        radius: root.elementRadius
        color: root.buttonColor
        property bool pressedTag: false

        ColumnLayout {
            anchors.fill: parent
            spacing: root.spacing
            visible: root.layout == Qt.Horizontal ? true : false

            Image {
                Layout.preferredWidth: Math.min(implicitWidth, root.width)
                Layout.preferredHeight: Math.min(implicitHeight, root.height)
                source: rectangle.pressedTag ? root.sourcePressed : root.source
                fillMode: Image.PreserveAspectFit
                Layout.alignment: Qt.AlignHCenter
            }

            Text {
                color: rectangle.pressedTag ? root.textColorPressed : root.textColor
                text: root.text
                Layout.preferredWidth: Math.min(contentWidth, root.width)
                Layout.preferredHeight: Math.min(contentHeight, root.height)
                wrapMode: Text.WordWrap
                font.pixelSize: Math.floor(root.height * (1 / 2))
                font.bold: root.fontBold
                // font.family: root.textFontFamily
                Layout.alignment: Qt.AlignHCenter
            }
        }

        RowLayout {
            anchors.centerIn: parent
            spacing: root.spacing
            visible: root.layout == Qt.Vertical ? true : false

            Image {
                Layout.preferredWidth: Math.min(implicitWidth, root.width)
                Layout.preferredHeight: Math.min(implicitHeight, root.height)
                source: rectangle.pressedTag ? root.sourcePressed : root.source
                fillMode: Image.PreserveAspectFit
                Layout.alignment: Qt.AlignHCenter
            }

            Text {
                color: rectangle.pressedTag ? root.textColorPressed : root.textColor
                text: root.text
                Layout.preferredWidth: Math.min(contentWidth, root.width)
                Layout.preferredHeight: Math.min(contentHeight, root.height)
                wrapMode: Text.WordWrap
                font.pixelSize: Math.floor(root.height * (1 / 2))
                font.bold: root.fontBold
                // font.family: root.textFontFamily
                Layout.alignment: Qt.AlignVCenter
            }
        }

        MouseArea {
            anchors.fill: parent

            onPressed: {
                rectangle.pressedTag = true;
            }

            onReleased: {
                rectangle.pressedTag = false;
            }

            onCanceled: {
                rectangle.pressedTag = false;
            }

            onClicked: root.clicked()
        }
    }
}
