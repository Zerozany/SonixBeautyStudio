pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Layouts
import SonixBeautyUI

Rectangle {
    id: root
    radius: root.elementRadius
    color: root.elementColor

    signal clicked

    property var text: null
    property url source: ""
    property url sourcePressed: ""
    property bool fontBold: false

    property bool pressedTag: false
    readonly property string textColorPressed: ThemeManager.currentTheme["textColorPressed"]
    readonly property string elementColor: ThemeManager.currentTheme["elementColor"]
    readonly property string textColor: ThemeManager.currentTheme["textColor"]
    readonly property int elementRadius: ThemeManager.styleSize["elementRadius"]
    readonly property int elementMargins: ThemeManager.styleSize["elementMargins"]
    readonly property int fontSize: ThemeManager.fontSize["L"]

    Loader {
        sourceComponent: root.width <= root.height ? verticalCom : horizontalCom
        anchors.centerIn: parent
    }

    Component {
        id: horizontalCom
        RowLayout {
            anchors.centerIn: parent
            spacing: 0
            Image {
                source: root.pressedTag ? root.sourcePressed : root.source
                fillMode: Image.PreserveAspectFit
                Layout.preferredWidth: parent.height
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }
            Text {
                text: root.text
                color: root.pressedTag ? root.textColorPressed : root.textColor
                wrapMode: Text.WordWrap
                font.pixelSize: Math.floor(root.height * 0.33)
                font.bold: root.fontBold
                // font.family: root.textFontFamily
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }
        }
    }

    Component {
        id: verticalCom
        ColumnLayout {
            anchors.centerIn: parent
            spacing: 0
            Image {
                source: root.pressedTag ? root.sourcePressed : root.source
                fillMode: Image.PreserveAspectFit
                Layout.preferredHeight: parent.width
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }
            Text {
                text: root.text
                color: root.pressedTag ? root.textColorPressed : root.textColor
                wrapMode: Text.WordWrap
                font.pixelSize: Math.floor(root.width * 0.2)
                font.bold: root.fontBold
                // font.family: root.textFontFamily
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onPressed: {
            root.pressedTag = true;
        }

        onPositionChanged: mouse => {
            if (!containsMouse && pressed) {
                root.pressedTag = false;
                mouse.accepted = false;
            }
        }

        onReleased: {
            root.pressedTag = false;
        }

        onCanceled: {
            root.pressedTag = false;
        }

        onClicked: root.clicked()
    }
}
