import QtQuick
import QtQuick.Controls
import QZeroZanyUI

Rectangle {
    id: root
    gradient: LoginGradient {}

    readonly property string elementColor: ThemeManager.currentTheme["elementColor"]
    readonly property int elementMargins: ElementStyle.elementMargins * 2
    readonly property url logoSource: "qrc:/qt/qml/SonixBeautyStudio/view/resource/SonixBeautyLogo.png"
    readonly property int lineTextWidth: ComponentConf.landScape ? root.width * 0.35 : root.width * 0.5
    readonly property int lineTextHeight: ComponentConf.landScape ? root.height * 0.08 : root.height * 0.05

    Image {
        anchors.top: parent.top
        anchors.topMargin: ComponentConf.landScape ? parent.height * 0.20 : parent.height * 0.30
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.Pad
        source: root.logoSource
    }

    LineTextField {
        id: userAccount
        placeText: "用户账号"
        source: "qrc:/qt/qml/SonixBeautyStudio/view/resource/setting.png"
        clearSource: "qrc:/qt/qml/SonixBeautyStudio/view/resource/clearInput.png"
        fontBold: true
        width: root.lineTextWidth
        height: root.lineTextHeight
        anchors.centerIn: parent
    }

    LineTextField {
        id: userPassword
        placeText: "用户密码"
        source: "qrc:/qt/qml/SonixBeautyStudio/view/resource/setting.png"
        passwordSource: "qrc:/qt/qml/SonixBeautyStudio/view/resource/settingPressed.png"
        passwordPressedSource: "qrc:/qt/qml/SonixBeautyStudio/view/resource/setting.png"
        clearSource: "qrc:/qt/qml/SonixBeautyStudio/view/resource/clearInput.png"
        fontBold: true
        password: true
        width: root.lineTextWidth
        height: root.lineTextHeight
        anchors.top: userAccount.bottom
        anchors.topMargin: root.elementMargins * 3
        anchors.horizontalCenter: parent.horizontalCenter
    }

    CheckBox {
        text: "记住密码"
        checked: false
        anchors.left: userPassword.left
        anchors.top: userPassword.bottom
        anchors.topMargin: root.elementMargins * 1
        anchors.horizontalCenter: parent.horizontalCenter

        onCheckedChanged: {
            console.log("是否勾选：", checked);
        }
    }

    NormalButton {
        text: "登录"
        color: "#7FFFD4"
        radius: 20
        fontBold: true
        width: root.lineTextWidth
        height: root.lineTextHeight
        anchors.top: userPassword.bottom
        anchors.topMargin: root.elementMargins * 10
        anchors.horizontalCenter: parent.horizontalCenter

        onClicked: {
            StackViewControl.stackPush(root, "qrc:/qt/qml/SonixBeautyStudio/view/mainPage/mainPage.qml");
        }
    }
}
