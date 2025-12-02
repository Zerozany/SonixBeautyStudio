import QtQuick
import QtQuick.Layouts

Rectangle {
    id: root
    radius: root.elementRadius
    color: root.elementColor

    property int edge: -1
    property var sidebarValueList: null

    readonly property int topEdge: 0
    readonly property int bottomEdge: 1
    readonly property int leftEdge: 2
    readonly property int rightEdge: 3
    readonly property string elementColor: ThemeManager.currentTheme["elementColor"]
    readonly property int elementRadius: ThemeManager.styleSize["elementRadius"]
    readonly property int elementMargins: ThemeManager.styleSize["elementMargins"]
    readonly property bool landScape: ComponentMethod.findTopLevelWindow(parent).width > ComponentMethod.findTopLevelWindow(parent).height

    ColumnLayout {}

    onEdgeChanged: {
        if (root.edge === root.topEdge || root.edge === root.bottomEdge) {
            if (landScape) {
                root.height = ComponentMethod.findTopLevelWindow(parent).height * 0.08;
            } else {
                root.height = ComponentMethod.findTopLevelWindow(parent).height * 0.05;
            }
            root.width = ComponentMethod.findTopLevelWindow(parent).width * 0.33;
        }
        if (root.edge === root.leftEdge || root.edge === root.rightEdge) {
            if (landScape) {
                root.width = ComponentMethod.findTopLevelWindow(parent).width * 0.05;
            } else {
                root.width = ComponentMethod.findTopLevelWindow(parent).width * 0.08;
            }
            root.height = ComponentMethod.findTopLevelWindow(parent).height * 0.33;
        }
        if (root.edge === root.topEdge || root.edge === root.bottomEdge) {
            root.x = (ComponentMethod.findTopLevelWindow(parent).width - root.width) / 2;
        }
        if (root.edge === root.leftEdge || root.edge === root.rightEdge) {
            root.y = (ComponentMethod.findTopLevelWindow(parent).height - root.height) / 2;
        }
    }

    SequentialAnimation {
        running: root.edge === root.leftEdge || root.edge === root.rightEdge

        NumberAnimation {
            target: root
            property: "x"
            duration: 150
            from: {
                if (root.edge === root.leftEdge) {
                    return -root.width;
                }
                if (root.edge === root.rightEdge) {
                    return ComponentMethod.findTopLevelWindow(root).width;
                } else {
                    return root.x;
                }
            }
            to: {
                if (root.edge === root.leftEdge) {
                    return root.elementMargins * 3;
                }
                if (root.edge === root.rightEdge) {
                    return ComponentMethod.findTopLevelWindow(root).width - root.width - root.elementMargins * 3;
                } else {
                    return root.x;
                }
            }
        }

        NumberAnimation {
            target: root
            property: "x"
            duration: 200
            to: {
                if (root.edge === root.leftEdge) {
                    return root.elementMargins;
                } else if (root.edge === root.rightEdge) {
                    return ComponentMethod.findTopLevelWindow(root).width - root.width - root.elementMargins;
                } else {
                    return root.x;
                }
            }
        }
    }

    SequentialAnimation {
        running: root.edge === root.topEdge || root.edge === root.bottomEdge

        NumberAnimation {
            target: root
            property: "y"
            duration: 150
            from: {
                if (root.edge === root.topEdge) {
                    return -root.height;
                }
                if (root.edge === root.bottomEdge) {
                    return ComponentMethod.findTopLevelWindow(root).height;
                } else {
                    return root.y;
                }
            }
            to: {
                if (root.edge === root.topEdge) {
                    return root.elementMargins * 3;
                }
                if (root.edge === root.bottomEdge) {
                    return ComponentMethod.findTopLevelWindow(root).height - root.height - root.elementMargins * 3;
                } else {
                    return root.y;
                }
            }
        }

        NumberAnimation {
            target: root
            property: "y"
            duration: 300
            to: {
                if (root.edge === root.topEdge) {
                    return root.elementMargins;
                } else if (root.edge === root.bottomEdge) {
                    return ComponentMethod.findTopLevelWindow(root).height - root.height - root.elementMargins;
                } else {
                    return root.y;
                }
            }
        }
    }
}
