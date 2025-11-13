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
        y: 0
        Component.onCompleted: {
            y = appWindow.height - Screen.desktopAvailableHeight;
        }
    }

    Rectangle {
        color: "blue"
        width: 50
        height: 50
        x: 0
        y: 0
        Component.onCompleted: {
            y = Screen.desktopAvailableHeight - height;
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
        console.log("qml:" + Screen.desktopAvailableHeight);
        console.log("qml:" + Screen.desktopAvailableWidth);
        AppConstants.mainWindowObject = appWindow;
        Utile.showApplicationTip(AppConstants.mainWindowObject, qsTr("Hello World!!!"));
    }
}
