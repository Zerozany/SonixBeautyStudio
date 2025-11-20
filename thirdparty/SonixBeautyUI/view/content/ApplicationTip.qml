import QtQuick

Rectangle {
    id: root
    x: parent ? (parent.width - root.width) / 2 : (Screen.width - root.width) / 2
    y: parent ? parent.height / 10 : Screen.height / 10
    width: parent ? parent.width / 3 : Screen.width / 3
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
