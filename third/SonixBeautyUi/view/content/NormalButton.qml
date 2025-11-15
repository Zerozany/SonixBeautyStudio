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
    property int layout: Qt.Horizontal

    property bool pressedTag: false
    readonly property string elementColor: ComponentConf.appColorTable["elementColor"]
    readonly property string textColor: ComponentConf.appColorTable["textColor"]
    readonly property string textColorPressed: ComponentConf.appColorTable["textColorPressed"]
    readonly property int elementRadius: ComponentConf.appSizeTable["elementRadius"]
    readonly property int elementMargins: ComponentConf.appSizeTable["elementMargins"]
    readonly property int pointSize: ComponentConf.pointSizeTable["L"]

    Loader {
        sourceComponent: root.layout === Qt.Horizontal ? horizontalCom : null
        onLoaded: {
            width = root.width;
            height = root.height;
        }
    }

    Component {
        id: horizontalCom
        RowLayout {
            anchors.fill: parent
            spacing: -50
            Image {
                source: root.pressedTag ? root.sourcePressed : root.source
                fillMode: Image.PreserveAspectFit
                Layout.preferredWidth: implicitWidth
                Layout.preferredHeight: implicitHeight
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }
            Text {
                text: root.text
                color: root.pressedTag ? root.textColorPressed : root.textColor
                wrapMode: Text.WordWrap
                font.pixelSize: Math.floor(root.height * 0.33)
                font.bold: root.fontBold
                // font.family: root.textFontFamily
                Layout.preferredWidth: contentWidth
                Layout.preferredHeight: contentHeight
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
