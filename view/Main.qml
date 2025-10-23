import QtQuick.Window
import SonixBeautyUi
import SonixBeautyStudio

AndroidWindow {
    id: appWindow
    // 设置全屏
    visibility: Window.AutomaticVisibility
    // 无边框
    // flags: Qt.FramelessWindowHint

    color: ThemeManager.currentTheme["backgroundColor"]

    App {
        id: qUi
        anchors.fill: parent
        backgroundColor: appWindow.color
    }

    Component.onCompleted: {
        Utile.showApplicationTip(appWindow, "backgroundColorbackgroundColorbackgroundColorbackgroundColor");
    }
}
