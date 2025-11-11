import QtQuick
import SonixBeautyUI

Rectangle {
    id: root
    radius: UIConstants.elementRadius ? UIConstants.elementRadius : Math.round(5 * Screen.devicePixelRatio)
    color: UIConstants.elementColor ? UIConstants.elementColor : Qt.rgba(1, 1, 1, 1)
    x: root.window ? root.window.x + (root.window.width - root.width) / 2 : (Screen.width - root.width) / 2
    y: root.window ? root.window.y + root.window.height / 4 : Screen.height / 4
    width: root.window ? root.window.width / 3 : Screen.width / 3

    property string text: ""
    property int interval: 2000
    property var window: null

    readonly property int pointSize: Math.round(14 * Screen.devicePixelRatio)

    Text {
        id: tipText
        anchors.fill: parent
        anchors.margins: UIConstants.margins
        color: UIConstants.textColor
        text: root.text
        wrapMode: Text.WrapAnywhere
        font.pointSize: root.pointSize
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
    }

    Component.onCompleted: {
        root.height = tipText.implicitHeight;
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
            script: Qt.callLater(function () {
                root.destroy();
            })
        }
    }
}
