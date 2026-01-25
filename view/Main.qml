import QtQuick
import QZeroSystem
import QZeroZanyUI
import SonixBeautyStudio
import QtQuick.Controls

ZeroWindow {
    id: mainWindow

    StackView {
        id: mainStackView
        anchors.fill: parent
        initialItem: LoginPage {}
    }

    // DynamicIsland {
    //     visible: !mainStackView.currentItem instanceof LoginPage
    // }

    ShortcutControl {
        sequences: [StandardKey.Back]
        onAndroidEvent: {
            mainStackView.pop();
        }
    }

    Component.onCompleted: {
        AppConstants.mainStackView = mainStackView;
    }
}
