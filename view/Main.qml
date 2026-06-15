import QtQuick
import QZeroSystem
import QZeroMaterialUI
import QtQuick.Controls

ZeroWindow {
    id: mainWindow

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

    MainStackLayout {
        anchors.fill: parent
        // initialItem: rect2
    }

    MaterialButton {
        id: btn
        anchors.horizontalCenter: parent.horizontalCenter
        y: 70
        text: qsTr("点击按钮")
        icon.source: "qrc:/qt/qml/SonixBeautyStudio/view/SonixBeauty/resource/setting.png"
        display: AbstractButton.TextUnderIcon

        onClicked: {
            // MainSignals.pushStack(rect1);
            // mainWindow.Material.theme = Material.Dark;
            // let rect = Qt.rect(50, 50, 100, 100);
            // ScreenShotUtils.imageFormat = ScreenShotUtils.JPG;
            // ScreenShotUtils.burstshot = 3;
            // ScreenShotUtils.screenshotItem(btn, "F:/DevelopFiles/SonixBeautyStudio/Screenshoot");
            // ScreenShotUtils.screenshotItem(btn, 50, 50, 100, 100, "F:/DevelopFiles/SonixBeautyStudio/Screenshoot");
            // ScreenShotUtils.screenshotItem(btn, rect, "F:/DevelopFiles/SonixBeautyStudio/Screenshoot");
            // RecordUtils.record();
            // Translator.language = ":/i18n/qml_en.qm";
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
            // MainSignals.pop();
        }
    }

    Component.onCompleted: {}
}
