import QtQuick
import SonixBeautySystem
import SonixBeautyStudio
import SonixBeautyUI

// import SonixBeautyUI

SonixBeautyWindow {
    id: appWindow
    color: appWindow.backgroundColor

    readonly property string backgroundColor: ThemeManager.currentTheme.backgroundColor

    Component.onCompleted: {
        AppConstants.mainWindowObject = appWindow;
        // ComponentMethod.showApplicationTip(appWindow, qsTr("Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!"));
    }
}
