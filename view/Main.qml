import QtQuick
import SonixBeautySystem

// import SonixBeautyUI

SonixBeautyWindow {
    id: mainWindow
    color: "blue"
    // color: mainWindow.backgroundColor

    // readonly property string backgroundColor: ThemeManager.currentTheme.backgroundColor

    Component.onCompleted: {
        // ComponentMethod.showApplicationTip(mainWindow, qsTr("Hello World!"), 2000);
    }
}
