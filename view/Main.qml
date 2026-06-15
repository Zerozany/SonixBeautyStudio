import QtQuick
import QZeroSystem
import QZeroMaterialUI
import QZeroAssistKit
import QtQuick.Controls.Material
// import SonixBeautyStudio
import QtQuick.Controls

// import QtQuick.Controls.impl

ZeroWindow {
    id: mainWindow
    // Material.foreground: '#15e248'

    // MaterialComboBox {
    //     x: 200
    //     y: 300
    //     displayText: "🥙选项:" + currentText
    //     model: ["模式1", "模式2", "模式3"]
    //     currentIndex: 2

    //     onActivated: {
    //         console.log(currentIndex);
    //         console.log(currentText);
    //         console.log(currentValue);
    //     }
    // }

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
    //     initialItem: rect2
    // }

    // Connections {
    //     target: AppConstants
    //     function onPushStack(_stackPage) {
    //         stackView.push(_stackPage);
    //     }
    // }

    MaterialButton {
        id: btn
        anchors.horizontalCenter: parent.horizontalCenter
        // width: implicitWidth
        // height: implicitHeight
        y: 70
        text: qsTr("点击按钮")
        icon.source: "qrc:/qt/qml/SonixBeautyStudio/view/resource/setting.png"
        display: AbstractButton.TextUnderIcon
        // scale: 1
        // flat: true
        // icon.width: 40
        // icon.height: 40
        // font.pixelSize: 22

        onClicked: {
            // mainWindow.Material.theme = Material.Dark;
            let rect = Qt.rect(50, 50, 100, 100);
            ScreenShotUtils.imageFormat = ScreenShotUtils.JPG;
            ScreenShotUtils.burstshot = 3;
            // ScreenShotUtils.screenshotItem(btn, "SonixBeautyStudio/Screenshoot");
            // ScreenShotUtils.screenshotItem(btn, 50, 50, 100, 100, "F:/DevelopFiles/SonixBeautyStudio/Screenshoot");
            // ScreenShotUtils.screenshotItem(btn, rect, "F:/DevelopFiles/SonixBeautyStudio/Screenshoot");
            // RecordUtils.record();
            Translator.language = ":/i18n/qml_en.qm";
        }

        // MaterialToolTip {
        //     text: "qrc:/qt/qml/SonixBeautyStudio/view/resource/setting.png"
        //     visible: (parent as MaterialButton).down
        //     opacity: 0.2
        //     color: "blue"
        // }
    }

    // DynamicIsland {
    //     visible: !stackView.currentItem instanceof LoginPage
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

    // MaterialSwitch {
    //     anchors.centerIn: parent

    //     onToggled: {
    //         if (checked) {
    //             console.log(checked);
    //         } else {
    //             console.log(checked);
    //         }
    //     }
    // }

    // PageBrightness {
    //     id: pageBrightness
    // }

    // Slider {
    //     width: 300
    //     anchors.bottom: parent.bottom
    //     anchors.horizontalCenter: parent.horizontalCenter

    //     from: 0
    //     to: 1

    //     value: pageBrightness.brightness

    //     onValueChanged: {
    //         pageBrightness.brightness = value;
    //     }
    // }

    Component.onCompleted: {
        // AppConstants.mainStackView = stackView;
        // console.log("XXXXXXXXX");
        // console.log("-----: " + ClassesManager.classesList.length);
    }
}
