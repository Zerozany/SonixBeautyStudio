import QtQuick
import SonixBeautyUi
import QtQuick.Controls
import QtQuick.Window

Item {
    id: root

    signal clicked

    property var text: null
    property var source: null
    property var sourcePressed: null
    property bool borderTag: false

    readonly property int margins: 5
    readonly property int borderWidth: 1
    readonly property string elementColor: "transparent"
    readonly property var elementRadius: ThemeManager.currentTheme["elementRadius"]
    readonly property color textColor: ThemeManager.currentTheme["textColor"]
    readonly property var borderColor: ThemeManager.currentTheme["borderColor"]

    onXChanged: {
        Qt.callLater(() => {
            imagePupup.x = root._popupX();
        });
    }

    onYChanged: {
        Qt.callLater(() => {
            imagePupup.y = root._popupY();
        });
    }

    onWidthChanged: {
        Qt.callLater(() => {
            imagePupup.x = root._popupX();
        });
    }

    onHeightChanged: {
        Qt.callLater(() => {
            imagePupup.y = root._popupY();
        });
    }

    function _popupX() {
        var pos = root.mapToItem(null, 0, 0);
        if (pos.x - (Math.abs(imagePupup.width - root.width) / 2) < 0) {
            console.log(1);
            console.log(pos.x);
            console.log((Math.abs(imagePupup.width - root.width) / 2));
            return 0;
        }
        if (pos.x + root.width + (Math.abs(imagePupup.width - root.width) / 2) > Screen.width) {
            console.log(2);
            return -(Math.abs(root.width - imagePupup.width));
        }
        console.log(3);
        if (root.width > imagePupup.width) {
            return -(imagePupup.width - root.width) / 2;
        } else if (root.width < imagePupup.width) {
            return (root.width - imagePupup.width) / 2;
        } else {
            return root.x;
        }
    }

    function _popupY() {
        var pos = root.mapToItem(null, 0, 0);
        if (pos.y + root.height + imagePupup.height + root.margins >= Screen.height) {
            return -(imagePupup.height + root.margins);
        }
        return root.height + root.margins;
    }

    Rectangle {
        id: rectangle
        anchors.fill: parent
        radius: root.elementRadius
        color: root.elementColor
        border.width: root.borderTag ? root.borderWidth : null
        border.color: root.borderTag ? root.borderColor : null
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
        height: root.height / 2
        width: imageText.implicitWidth + (root.margins * 2)
        visible: rectangle.pressedTag && root.text.length ? true : false

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

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onPressed: {
            rectangle.pressedTag = true;
        }

        onPositionChanged: mouse => {
            if (!containsMouse && pressed) {
                rectangle.pressedTag = false;
                mouse.accepted = false;
            }
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
