pragma Singleton
import QtQuick

QtObject {
    readonly property bool landScape: Screen.orientation === Qt.LandscapeOrientation || Screen.orientation === Qt.InvertedLandscapeOrientation ? true : false
}
