import QtQuick
import QtQuick.Layouts
import QZeroMaterialUI

LoginBackdrop {
    id: root

    readonly property int elementRadius: ElementStyle.elementRadius
    readonly property int elementMargins: ElementStyle.elementMargins
    readonly property size textFieldSize: Qt.size(parent.width * 0.3, parent.height * 0.065)
    readonly property size loginOptionsSize: Qt.size(parent.width * 0.3, parent.height * 0.06)

    ColumnLayout {
        width: parent.width * 0.35
        height: parent.height * 0.35
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 0.125

        NormalTextField {
            id: userAccount
            placeholderText: qsTr("用户账号")
            source: "qrc:/qt/qml/SonixBeautyStudio/view/resource/setting.png"
            Layout.preferredWidth: root.textFieldSize.width
            Layout.preferredHeight: root.textFieldSize.height
            Layout.alignment: Qt.AlignHCenter
        }

        NormalTextField {
            id: userPassword
            placeholderText: qsTr("用户密码")
            source: "qrc:/qt/qml/SonixBeautyStudio/view/resource/setting.png"
            echoMode: TextInput.Password
            Layout.preferredWidth: root.textFieldSize.width
            Layout.preferredHeight: root.textFieldSize.height
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: root.elementMargins * 2
        }

        RowLayout {
            Layout.preferredWidth: root.loginOptionsSize.width
            Layout.preferredHeight: root.loginOptionsSize.height
            Layout.alignment: Qt.AlignHCenter

            NormalCheckBox {
                text: qsTr("记住密码")
                checked: false
                Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
                Layout.leftMargin: root.elementMargins

                onCheckedChanged: {
                    // console.log("是否勾选：", checked);
                }
            }

            NormalButton {
                text: qsTr("登录遇到问题")
                textColor: '#48c49a'
                color: "transparent"
                flat: true
                Layout.preferredWidth: doubtTextMetrucs.textWidth
                Layout.preferredHeight: parent.height
                Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                Layout.rightMargin: root.elementMargins

                TermsTextMetrucs {
                    id: doubtTextMetrucs
                    text: parent.text
                    font: parent.font
                }
            }
        }

        Row {
            Layout.preferredWidth: root.loginOptionsSize.width * 0.8
            Layout.preferredHeight: root.loginOptionsSize.height
            Layout.alignment: Qt.AlignHCenter

            NormalCheckBox {
                text: qsTr("我已阅读并同意")
                checked: false
                radius: 18
                anchors.verticalCenter: parent.verticalCenter

                onCheckedChanged: {
                    // console.log("是否勾选：", checked);
                }
            }

            NormalButton {
                text: qsTr("《服务条款》《隐私政策》")
                textColor: '#48c49a'
                color: "transparent"
                flat: true
                width: termsTextMetrucs.textWidth
                height: parent.height
                anchors.verticalCenter: parent.verticalCenter

                TermsTextMetrucs {
                    id: termsTextMetrucs
                    text: parent.text
                    font: parent.font
                }
            }
        }

        NormalButton {
            text: qsTr("登录")
            color: "#7FFFD4"
            radius: root.elementRadius * 4
            Layout.preferredWidth: root.width * 0.2
            Layout.preferredHeight: root.height * 0.06
            Layout.alignment: Qt.AlignHCenter

            onClicked: {
                // AppConstants.mainStackView.push("qrc:/qt/qml/SonixBeautyStudio/view/mainPage/mainPage.qml");
            }
        }

        NormalButton {
            text: qsTr("离线模式")
            color: "#7FFFD4"
            textColor: "#A9A9A9"
            radius: root.elementRadius * 4
            Layout.preferredWidth: root.width * 0.2
            Layout.preferredHeight: root.height * 0.06
            Layout.alignment: Qt.AlignHCenter

            onClicked: {
                // AppConstants.mainStackView.push("qrc:/qt/qml/SonixBeautyStudio/view/mainPage/mainPage.qml");
                // Translator.setLanguage(":/i18n/qml_en.qm");
            }
        }
    }
}
