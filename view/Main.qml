import QtQuick
import SonixBeautySystem
import SonixBeautyStudio
import SonixBeautyUI

SonixBeautyWindow {
    id: appWindow
    color: appWindow.backgroundColor

    readonly property string backgroundColor: ThemeManager.currentTheme.backgroundColor

    Component.onCompleted: {
        AppConstants.mainWindowObject = appWindow;
        ComponentMethod.showApplicationTip(AppConstants.mainWindowObject, qsTr("Hello World!"), 2000);
    }
}
