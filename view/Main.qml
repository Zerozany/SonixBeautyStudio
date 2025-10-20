import QtQuick.Window
import SonixBeautyUi

Window {
    id: appWindow
    // 设置全屏
    visibility: Window.FullScreen
    // 无边框
    flags: Qt.FramelessWindowHint

    color: ThemeManager.currentTheme["backgroundColor"]

    App {
        id: qUi
        anchors.fill: parent
        backgroundColor: appWindow.color
    }

    Component.onCompleted: {}
}
