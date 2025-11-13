import QtQuick
import SonixBeautyJNI

import SonixBeautyUI
import SonixBeautyStudio

SonixBeautyWindow {
    id: appWindow

    color: "green"

    Rectangle {
        color: "blue"
        width: 50
        height: 50
        x: 0
        y: 25
    }

    Rectangle {
        color: "blue"
        width: 50
        height: 50
        x: 0
        y: 0
        Component.onCompleted: {
            y = appWindow.height - height - 20;
        }
    }

    Rectangle {
        color: "blue"
        width: 50
        height: 50
        x: 0
        y: 0
        Component.onCompleted: {
            x = Screen.desktopAvailableWidth - width;
            y = Screen.desktopAvailableHeight - height;
        }
    }

    Component.onCompleted: {
        AppConstants.mainWindowObject = appWindow;
        Utile.showApplicationTip(AppConstants.mainWindowObject, qsTr("Hello World!!!"));
    }
}
