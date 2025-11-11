import QtQuick
// import SonixBeautyJNI

import SonixBeautyWIN
import SonixBeautyStudio

SonixBeautyWindow {
    id: appWindow

    Component.onCompleted: {
        AppConstants.mainWindowObject = appWindow;
    }
}
