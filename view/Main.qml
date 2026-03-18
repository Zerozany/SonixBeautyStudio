import QtQuick
import QZeroSystem
import QZeroMaterialUI
import QtQuick.Controls.Material

// import SonixBeautyStudio
// import QtQuick.Controls
// import QtQuick.Controls.impl

ZeroWindow {
    id: mainWindow
    Material.foreground: '#15e248'

    MaterialButton {
        anchors.horizontalCenter: parent.horizontalCenter
        y: 70
        text: "XXXX"
        icon.source: "qrc:/qt/qml/SonixBeautyStudio/view/resource/setting.png"
        scale: 1
        // flat: true

        onClicked: {
            // mainWindow.Material.theme = Material.Dark;
        }

        // MaterialToolTip {
        //     text: "qrc:/qt/qml/SonixBeautyStudio/view/resource/setting.png"
        //     visible: (parent as MaterialButton).down
        //     opacity: 0.2
        //     color: "blue"
        // }
    }

    MaterialComboBox {
        x: 200
        y: 300
        displayText: "🥙选项:" + currentText
        model: ["模式1", "模式2", "模式3"]
        currentIndex: 2

        onActivated: {
            console.log(currentIndex);
            console.log(currentText);
            console.log(currentValue);
        }
    }

    // property url cursorSource: "qrc:/qt/qml/QZeroMaterialUI/view/resource/normalComboBox/cursor.png"

    // readonly property string elementColor: ThemeManager.currentTheme["ElementColor"]
    // readonly property string borderDefaultColor: "#CCCCCC"
    // readonly property int elementRadius: ElementStyle.elementRadius
    // readonly property int elementMargins: ElementStyle.elementMargins
    // readonly property int elementSpacing: ElementStyle.elementSpacing
    // readonly property string fontFamily: ThemeFont.fontFamily
    // readonly property size cursorSize: Qt.size(12, 12)

    // Item {
    //     anchors.fill: parent

    //     TapHandler {
    //         onTapped: {
    //             parent.forceActiveFocus();
    //         }
    //     }

    //     MaterialTextField {
    //         id: normalTextField
    //         x: 200
    //         y: 300
    //         placeholderText: qsTr("用户账号/手机号")
    //         option: ColorImage {
    //             source: "qrc:/qt/qml/SonixBeautyStudio/view/resource/setting.png"
    //             fillMode: Image.PreserveAspectFit
    //             color: Material.foreground
    //         }
    //         echoMode: TextInput.Password
    //         passwordSource: "qrc:/qt/qml/SonixBeautyStudio/view/resource/setting.png"
    //     }
    // }

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
