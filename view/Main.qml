import QtQuick
// import SonixBeautyJNI

import SonixBeautyWIN
import SonixBeautyUI
import SonixBeautyStudio

SonixBeautyWindow {
    id: appWindow

    color: ThemeManager.currentTheme["backgroundColor"]

    App {
        id: qUi
        anchors.fill: parent
        backgroundColor: appWindow.color
    }

    Component.onCompleted: {
        AppConstants.mainWindowObject = appWindow;
    }
}
