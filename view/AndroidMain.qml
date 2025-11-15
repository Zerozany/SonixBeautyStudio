import QtQuick
import SonixBeautyJNI
import SonixBeautyUI

// import SonixBeautyStudio

SonixBeautyWindow {
    id: appWindow

    color: ComponentConf.appColorTable["backgroundColor"]

    NormalButton {
        text: "Horizontal"
        layout: Qt.Horizontal
        source: "qrc:/view/resource/HomePageIcons/connect.png"
        sourcePressed: "qrc:/view/resource/HomePageIcons/connectPressed.png"
        fontBold: true
        width: 100
        height: 45
        x: 50
        y: 50
    }

    NormalButton {
        text: "Vertical"
        layout: Qt.Vertical
        source: "qrc:/view/resource/HomePageIcons/connect.png"
        sourcePressed: "qrc:/view/resource/HomePageIcons/connectPressed.png"
        fontBold: false
        width: 60
        height: 120
        x: 150
        y: 150
    }

    Component.onCompleted: {

        // AppConstants.mainWindowObject = appWindow;
        ComponentMethod.showApplicationTip(appWindow, qsTr("Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!Hello World!!!"));
    }
}
