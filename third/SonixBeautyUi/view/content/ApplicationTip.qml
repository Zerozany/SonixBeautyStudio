import QtQuick
import QtQuick.Window
import SonixBeautyUI

Rectangle {
    id: root
    x: parentWindow ? (parentWindow.width - root.width) / 2 : (Screen.width - root.width) / 2
    y: parentWindow ? parentWindow.height / 10 : Screen.height / 10
    width: parentWindow ? parentWindow.width / 3 : Screen.width / 3
    radius: root.elementRadius
    color: root.elementColor

    property string text: ""
    property int interval: 2000
    property var parentWindow: null

    readonly property string elementColor: ComponentConf.appColorTable["elementColor"]
    readonly property string textColor: ComponentConf.appColorTable["textColor"]
    readonly property int elementRadius: ComponentConf.appSizeTable["elementRadius"]
    readonly property int elementMargins: ComponentConf.appSizeTable["elementMargins"]
    readonly property int pointSize: ComponentConf.pointSizeTable["L"]

    Text {
        anchors.fill: parent
        anchors.margins: root.elementMargins
        text: root.text
        color: root.textColor
        font.pointSize: root.pointSize
        wrapMode: Text.WrapAnywhere
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter

        Component.onCompleted: {
            root.height = implicitHeight + root.elementMargins * 2;
        }
    }

    SequentialAnimation {
        running: root.visible && root.parentWindow.active
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
            script: Qt.callLater(() => root.destroy)
        }
    }
}
