pragma ComponentBehavior: Bound
import QtQuick
import SonixBeautyUi
import QtQuick.Controls
import QtQuick.Window

Item {
    id: root

    property var imageButtonList: null

    readonly property int spacing: 5
    readonly property int margins: 10
    readonly property int imageButtonSize: 50
    readonly property var elementRadius: ThemeManager.currentTheme["elementRadius"]
    readonly property var elementColor: ThemeManager.currentTheme["elementColor"]

    Rectangle {
        anchors.fill: parent
        anchors.margins: root.margins
        radius: root.elementRadius
        color: root.elementColor

        Column {
            anchors.fill: parent
            anchors.margins: root.margins
            spacing: root.spacing

            Repeater {
                id: repeater
                model: root.imageButtonList
                delegate: ImageButton {
                    width: root.imageButtonSize
                    height: root.imageButtonSize
                    anchors.horizontalCenter: parent.horizontalCenter
                    required property var modelData
                    text: modelData.text
                    source: modelData.source
                    sourcePressed: modelData.sourcePressed
                    // onClicked: modelData.clicked
                }
            }
        }
    }
}
