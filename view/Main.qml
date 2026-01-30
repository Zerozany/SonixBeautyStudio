import QtQuick
import QZeroSystem
import QZeroMaterialUI
import SonixBeautyStudio
import QtQuick.Controls

ZeroWindow {
    id: mainWindow

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: LoginPage {}
    }

    DynamicIsland {
        visible: !stackView.currentItem instanceof LoginPage
    }

    ShortcutControl {
        sequences: [StandardKey.Back]
        onAndroidEvent: {
            stackView.pop();
        }
    }

    Component.onCompleted: {
        AppConstants.mainStackView = stackView;
    }
}
