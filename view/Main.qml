import QtQuick
import SonixBeautySystem
import SonixBeautyUI

SonixBeautyWindow {
    id: mainWindow
    color: mainWindow.backgroundColor

    readonly property string backgroundColor: ThemeManager.currentTheme.backgroundColor

    Component.onCompleted: {
        AppConstants.mainWindowObject = mainWindow;
        ComponentMethod.showApplicationTip(AppConstants.mainWindowObject, qsTr("Hello World!"), 2000);
    }
}
