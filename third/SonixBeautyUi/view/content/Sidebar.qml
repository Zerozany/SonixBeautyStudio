pragma ComponentBehavior: Bound
import QtQuick
import SonixBeautyUI
import QtQuick.Window
import QtQuick.Layouts

Item {
    id: root

    property var layout: sidebarLayout.Right
    property var imageButtonList: null

    readonly property var sidebarLayout: ({
            Left: 0,
            Right: 1
        })
    readonly property int spacing: 5
    readonly property int margins: 10
    readonly property int imageButtonSize: root.width - (root.margins * 2)
    readonly property var elementRadius: ThemeManager.currentTheme["elementRadius"]
    readonly property var elementColor: ThemeManager.currentTheme["elementColor"]

    Rectangle {
        anchors.fill: parent
        radius: root.elementRadius
        color: root.elementColor

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: root.margins
            spacing: root.spacing

            Repeater {
                id: repeater
                model: root.imageButtonList
                delegate: ImageButton {
                    width: root.imageButtonSize
                    height: root.imageButtonSize
                    required property var modelData
                    text: modelData.text
                    source: modelData.source
                    sourcePressed: modelData.sourcePressed
                    borderTag: modelData.borderTag
                    // onClicked: modelData.clicked
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }
    }

    SequentialAnimation {
        running: true

        NumberAnimation {
            target: root
            property: "x"
            duration: 150
            from: root.layout === root.sidebarLayout.Left ? -(root.width) : Screen.width
            to: root.layout === root.sidebarLayout.Left ? 20 : Screen.width - root.width - 20
        }

        NumberAnimation {
            target: root
            property: "x"
            duration: 200
            to: root.layout === root.sidebarLayout.Left ? 10 : Screen.width - root.width - 10
        }

        onStopped: {}
    }
}
