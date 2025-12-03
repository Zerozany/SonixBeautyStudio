import QtQuick
import QZeroSystem
import QZeroZanyUI

ZeroWindow {
    id: mainWindow
    color: mainWindow.backgroundColor

    readonly property string backgroundColor: ThemeManager.currentTheme["backgroundColor"]

    Component.onCompleted: {
        ComponentMethod.showApplicationTip(mainWindow, qsTr("Hello World!"), 2000);
    }
}
