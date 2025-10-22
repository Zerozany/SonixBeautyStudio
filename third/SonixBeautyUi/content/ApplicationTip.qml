import QtQuick
import SonixBeautyUi
import QtQuick.Window

Rectangle {
    id: root
    radius: elementRadius
    color: elementColor
    x: Screen.width / 2 - root.width / 2
    y: Screen.height / 4
    width: Screen.width / 3

    property var text: null
    property var interval: 2000

    readonly property int margins: 5
    readonly property int pointSize: 14
    readonly property var elementRadius: ThemeManager.currentTheme["elementRadius"]
    readonly property var elementColor: ThemeManager.currentTheme["elementColor"]
    readonly property color textColor: ThemeManager.currentTheme["textColor"]

    Text {
        id: tipText
        anchors.fill: parent
        anchors.margins: root.margins
        color: root.textColor
        text: root.text
        wrapMode: Text.WrapAnywhere
        font.pointSize: root.pointSize
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Component.onCompleted: {
        if (Screen) {
            root.height = tipText.implicitHeight;
        }
    }

    SequentialAnimation {
        running: true
        ParallelAnimation {
            OpacityAnimator {
                target: root
                duration: 300
                from: 0
                to: 1
            }
            ScaleAnimator {
                target: root
                duration: 300
                from: 0.8
                to: 1
                easing.type: Easing.OutQuart
            }
        }
        PauseAnimation {
            duration: root.interval
        }
        OpacityAnimator {
            target: root
            duration: 300
            to: 0
        }
        ScriptAction {
            script: root.destroy()
        }
    }
}
