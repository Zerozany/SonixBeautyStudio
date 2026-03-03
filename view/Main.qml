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

    // Drawer {
    //     id: drawer
    //     width: 0.66 * mainWindow.width
    //     height: mainWindow.height
    //     opacity: 0.5

    //     Label {
    //         text: "Content goes here!"
    //         anchors.centerIn: parent
    //     }
    // }

    // NormalSwitch {
    //     anchors.centerIn: parent

    //     onToggled: {
    //         if (checked) {
    //             drawer.open();
    //             console.log(checked);
    //         } else {
    //             console.log(checked);
    //             drawer.close();
    //         }
    //     }
    // }

    Component.onCompleted: {
        AppConstants.mainStackView = stackView;
    }
}
