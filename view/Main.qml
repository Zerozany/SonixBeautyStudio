import QtQuick
// import SonixBeautyJNI

import SonixBeautyWIN
import SonixBeautyUI

SonixBeautyWindow {
    id: appWindow

    color: ThemeManager.currentTheme["backgroundColor"]

    App {
        id: qUi
        anchors.fill: parent
        backgroundColor: appWindow.color
    }

    Component.onCompleted: {
        Utile.mainWindowObject = appWindow;
    }
}
