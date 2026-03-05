import QtQuick
import QZeroSystem
import QZeroMaterialUI
import QtQuick.Controls.Material

// import SonixBeautyStudio
import QtQuick.Controls

ZeroWindow {
    id: mainWindow

    Button {
        text: qsTr("登录")
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        icon.source: "qrc:/qt/qml/SonixBeautyStudio/view/resource/setting.png"
    }

    NormalButton {
        width: 120
        height: 40
        text: qsTr("登录")
        anchors.centerIn: parent
        // Material.background: '#c519e7'
        radius: 10
        icon.source: "qrc:/qt/qml/SonixBeautyStudio/view/resource/setting.png"
        // Material.foreground: "red"
        icon.color: "red"
    }

    // StackView {
    //     id: stackView
    //     anchors.fill: parent
    //     initialItem: LoginPage {}
    // }

    // DynamicIsland {
    //     visible: !stackView.currentItem instanceof LoginPage
    // }

    // TabBar {
    //     width: parent.width
    //     anchors.top: parent.top
    //     anchors.horizontalCenter: parent.horizontalCenter

    //     TabButton {
    //         text: qsTr("Home")
    //     }
    //     TabButton {
    //         text: qsTr("Discover")
    //     }
    //     TabButton {
    //         text: qsTr("Activity")
    //     }
    // }

    ShortcutControl {
        sequences: [StandardKey.Back]
        onAndroidEvent: {
            // stackView.pop();
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
        // AppConstants.mainStackView = stackView;
    }
}
