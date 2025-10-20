import QtQuick
import SonixBeautyUi
import QtQuick.Controls
import QtQuick.Window

Item {
    id: root
    property var text: null
    property var source: null
    property var sourcePressed: null

    readonly property int margins: 5
    readonly property string elementColor: "transparent"
    readonly property var elementRadius: ThemeManager.currentTheme["elementRadius"]
    readonly property color textColor: ThemeManager.currentTheme["textColor"]

    signal clicked

    function _popupX() {
        var pos = root.mapToItem(null, 0, 0);
        if (pos.x - (imagePupup.width / 2) + (root.width / 2) <= 0) {
            return root.x + root.margins;
        }
        if (pos.x + imagePupup.width >= Screen.width) {
            return root.width - imagePupup.width - root.margins;
        }
        return (root.width / 2) - (imagePupup.width / 2);
    }

    function _popupY() {
        var pos = root.mapToItem(null, 0, 0);
        if (pos.y + root.height + imagePupup.height >= Screen.height) {
            return -imagePupup.height;
        }
        return root.height;
    }

    Rectangle {
        id: rectangle
        anchors.fill: parent
        radius: root.elementRadius
        color: root.elementColor
        property bool pressedTag: false

        Image {
            anchors.fill: parent
            anchors.margins: root.margins
            source: rectangle.pressedTag ? root.sourcePressed : root.source
            fillMode: Image.PreserveAspectFit
        }
    }

    Popup {
        id: imagePupup
        modal: false
        focus: false
        height: rectangle.height / 2
        visible: rectangle.pressedTag ? true : false

        contentItem: Rectangle {
            anchors.fill: parent
            color: root.elementColor
            radius: root.elementRadius

            Text {
                id: imageText
                text: root.text
                width: contentWidth
                height: imagePupup.height
                color: root.textColor
                font.pixelSize: Math.floor(height * (1 / 2))
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    Component.onCompleted: {
        imagePupup.width = imageText.implicitWidth + (root.margins * 2);
        imagePupup.x = _popupX();
        imagePupup.y = _popupY();
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
