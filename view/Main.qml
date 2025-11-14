import QtQuick
import QtQuick.Controls
import SonixBeautyJNI

// import SonixBeautyUI
// import SonixBeautyStudio

SonixBeautyWindow {
    id: appWindow

    color: "blue"

    Button {
        x: 344
        y: 100
        text: "World"
        width: 200
        height: 100
    }

    Text {
        x: 100
        y: 100
        text: "World"
        width: 200
        height: 100
    }

    Component.onCompleted: {
        // AppConstants.mainWindowObject = appWindow;
        // Utile.showApplicationTip(AppConstants.mainWindowObject, qsTr("Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!"));
    }
}
