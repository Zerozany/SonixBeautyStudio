import QtQuick

Rectangle {
    id: root
    x: (parent.width - root.width) * 0.5
    y: ComponentConf.landScape ? parent.height * 0.2 : parent.height * 0.1
    width: ComponentConf.landScape ? parent.width * 0.5 : parent.width * 0.8
    radius: root.elementRadius
    color: root.elementColor

    property string text: ""
    property int interval: 2000

    readonly property string elementColor: ThemeManager.currentTheme["elementColor"]
    readonly property string textColor: ThemeManager.currentTheme["textColor"]
    readonly property int elementRadius: ThemeManager.styleSize["elementRadius"]
    readonly property int elementMargins: ThemeManager.styleSize["elementMargins"]
    readonly property int fontSize: ThemeManager.fontSize["L"]

    Text {
        anchors.fill: parent
        anchors.margins: root.elementMargins
        text: root.text
        color: root.textColor
        font.pointSize: root.fontSize
        wrapMode: Text.WrapAnywhere
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter

        Component.onCompleted: {
            root.height = implicitHeight + root.elementMargins * 2;
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
        onStopped: {
            root.destroy();
        }
    }
}
