import QtQuick
import QZeroZanyUI

Rectangle {
    id: root
    gradient: LoginGradient {}

    readonly property string elementColor: ThemeManager.currentTheme["elementColor"]
    readonly property int elementMargins: ElementStyle.elementMargins * 2
    readonly property url logoSource: "qrc:/qt/qml/SonixBeautyStudio/view/resource/SonixBeautyLogo.png"
    readonly property int normalTextWidth: ComponentConf.landScape ? root.width * 0.35 : root.width * 0.5
    readonly property int normalTextHeight: ComponentConf.landScape ? root.height * 0.08 : root.height * 0.05

    Image {
        id: logo
        anchors.top: parent.top
        anchors.topMargin: ComponentConf.landScape ? parent.height * 0.20 : parent.height * 0.30
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.Pad
        source: root.logoSource
    }

    NormalTextField {
        id: userAccount
        placeholderText: "用户账号"
        source: "qrc:/qt/qml/SonixBeautyStudio/view/resource/setting.png"
        clearSource: "qrc:/qt/qml/SonixBeautyStudio/view/resource/clearInput.png"
        width: root.normalTextWidth
        height: root.normalTextHeight
        anchors.centerIn: parent
    }

    NormalTextField {
        id: userPassword
        placeholderText: "用户密码"
        source: "qrc:/qt/qml/SonixBeautyStudio/view/resource/setting.png"
        passwordSource: "qrc:/qt/qml/SonixBeautyStudio/view/resource/settingPressed.png"
        pressedPasswordSource: "qrc:/qt/qml/SonixBeautyStudio/view/resource/setting.png"
        clearSource: "qrc:/qt/qml/SonixBeautyStudio/view/resource/clearInput.png"
        width: root.normalTextWidth
        height: root.normalTextHeight
        anchors.top: userAccount.bottom
        anchors.topMargin: root.elementMargins * 3
        anchors.horizontalCenter: parent.horizontalCenter
        echoMode: TextInput.Password
    }

    NormalCheckBox {
        text: "记住密码"
        checked: false
        anchors.left: userPassword.left
        anchors.top: userPassword.bottom
        anchors.topMargin: root.elementMargins * 1

        onCheckedChanged: {
            // console.log("是否勾选：", checked);
        }
    }

    NormalButton {
        text: "登录"
        color: "#7FFFD4"
        radius: 20
        width: root.normalTextWidth
        height: root.normalTextHeight
        anchors.top: userPassword.bottom
        anchors.topMargin: root.elementMargins * 10
        anchors.horizontalCenter: parent.horizontalCenter

        onClicked: {
            AppConstants.mainStackView.push("qrc:/qt/qml/SonixBeautyStudio/view/mainPage/mainPage.qml");
        }
    }
}
