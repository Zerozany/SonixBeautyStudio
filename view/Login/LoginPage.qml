import QtQuick
import QtQuick.Layouts

import QZeroZanyUI

LoginBackdrop {
    id: root

    ColumnLayout {
        width: parent.width * 0.5
        height: parent.height * 0.5
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 0.125
    }

    NormalTextField {
        id: userAccount
        placeholderText: "用户账号"
        source: "qrc:/qt/qml/SonixBeautyStudio/view/resource/setting.png"
        width: 200
        height: 40
        anchors.centerIn: parent
    }

    NormalTextField {
        id: userPassword
        placeholderText: "用户密码"
        source: "qrc:/qt/qml/SonixBeautyStudio/view/resource/setting.png"
        width: 200
        height: 40
        anchors.top: userAccount.bottom
        anchors.topMargin: root.elementMargins * 3
        anchors.horizontalCenter: parent.horizontalCenter
        echoMode: TextInput.Password
    }

    // NormalCheckBox {
    //     text: "记住密码"
    //     checked: false
    //     anchors.left: userPassword.left
    //     anchors.top: userPassword.bottom
    //     anchors.topMargin: root.elementMargins * 1

    //     onCheckedChanged: {
    //         // console.log("是否勾选：", checked);
    //     }
    // }

    // NormalButton {
    //     text: "登录"
    //     color: "#7FFFD4"
    //     radius: 20
    //     width: root.normalTextWidth
    //     height: root.normalTextHeight
    //     anchors.top: userPassword.bottom
    //     anchors.topMargin: root.elementMargins * 10
    //     anchors.horizontalCenter: parent.horizontalCenter

    //     onClicked: {
    //         AppConstants.mainStackView.push("qrc:/qt/qml/SonixBeautyStudio/view/mainPage/mainPage.qml");
    //     }
    // }
}
