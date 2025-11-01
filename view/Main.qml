import QtQuick
import SonixBeautyUi
import SonixBeautyStudio
import JNIModule

AndroidWindow {
    id: appWindow
    // 设置全屏
    visibility: Window.AutomaticVisibility
    // 无边框
    // flags: Qt.FramelessWindowHint
    visible: true

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
