import QtQuick
import SonixBeautyUI
import SonixBeautyJNI
import SonixBeautyWin

SonixBeautyWindow {
    id: appWindow
    // 无边框
    // flags: Qt.FramelessWindowHint

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
