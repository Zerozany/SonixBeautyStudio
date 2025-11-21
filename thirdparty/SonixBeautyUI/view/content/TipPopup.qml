import QtQuick

Rectangle {
    id: root
    radius: root.elementRadius
    color: root.elementColor

    property string text: ""

    readonly property string elementColor: ThemeManager.currentTheme["elementColor"]
    readonly property string textColor: ThemeManager.currentTheme["textColor"]
    readonly property int elementRadius: ThemeManager.styleSize["elementRadius"]
    readonly property int elementMargins: ThemeManager.styleSize["elementMargins"]
    readonly property int elementSpacing: ThemeManager.styleSize["elementSpacing"]
    readonly property int fontSize: ThemeManager.fontSize["L"]

    Text {
        anchors.centerIn: parent
        text: root.text
        width: contentWidth
        height: contentHeight
        color: root.textColor
        font.pixelSize: root.fontSize
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter

        Component.onCompleted: {
            root.width = contentWidth + 2 * (root.elementMargins);
            root.height = contentHeight + 2 * (root.elementMargins);
        }
    }

    onVisibleChanged: {
        x = root._popupX();
        y = root._popupY();
    }

    function _popupX(): real {
        let relativePoint = parent.mapToItem(null, 0, 0);
        if (parent.width >= root.width) {
            return (parent.width - root.width) / 2;
        }
        if (relativePoint.x - (root.width - parent.width) / 2 <= 0) {
            return 0;
        }
        if (relativePoint.x + parent.width + (root.width - parent.width) / 2 >= ComponentMethod.findTopLevelWindow(parent).width) {
            return parent.width - root.width;
        }
        return (parent.width - root.width) / 2;
    }

    function _popupY(): real {
        let relativePoint = parent.mapToItem(null, 0, 0);
        if (relativePoint.y < root.height + root.elementMargins) {
            return parent.height + root.elementMargins;
        }
        if (relativePoint.y + parent.height + root.height + root.elementMargins > ComponentMethod.findTopLevelWindow(parent).height) {
            return -root.height - root.elementMargins;
        }
        return parent.height + root.elementMargins;
    }
}
