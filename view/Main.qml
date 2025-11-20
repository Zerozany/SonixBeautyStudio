import QtQuick
import SonixBeautySystem
import SonixBeautyStudio
import SonixBeautyUI
import "qrc:/view/ApplicationTipManager.js" as TipManager

SonixBeautyWindow {
    id: appWindow
    color: appWindow.backgroundColor

    readonly property string backgroundColor: ThemeManager.currentTheme.backgroundColor

    Component.onCompleted: {
        AppConstants.mainWindowObject = appWindow;
        TipManager.showApplicationTip(AppConstants.mainWindowObject, qsTr("Hello World!"), 2000);
    }
}
