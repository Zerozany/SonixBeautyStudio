import QtQuick
import SonixBeautyStudio
import QZeroMaterialUI
import QtQuick.Controls

Item {
    id: root

    property LoginUser loginUser: LoginUser {}

    Connections {
        target: root.loginUser
        function onUserPhoneChanged() {
            loginUserInfo.text = "用户账号:" + root.loginUser.userPhone + "\n用户密码:" + root.loginUser.userPassword + "\n用户部门:" + root.loginUser.userDepartment + "\n用户医院:" + root.loginUser.userHospital + "\n用户昵称:" + root.loginUser.userNickname;
        }
        function onUserPasswordChanged() {
            loginUserInfo.text = "用户账号:" + root.loginUser.userPhone + "\n用户密码:" + root.loginUser.userPassword + "\n用户部门:" + root.loginUser.userDepartment + "\n用户医院:" + root.loginUser.userHospital + "\n用户昵称:" + root.loginUser.userNickname;
        }
        function onUserDepartmentChanged() {
            loginUserInfo.text = "用户账号:" + root.loginUser.userPhone + "\n用户密码:" + root.loginUser.userPassword + "\n用户部门:" + root.loginUser.userDepartment + "\n用户医院:" + root.loginUser.userHospital + "\n用户昵称:" + root.loginUser.userNickname;
        }
        function onUserHospitalChanged() {
            loginUserInfo.text = "用户账号:" + root.loginUser.userPhone + "\n用户密码:" + root.loginUser.userPassword + "\n用户部门:" + root.loginUser.userDepartment + "\n用户医院:" + root.loginUser.userHospital + "\n用户昵称:" + root.loginUser.userNickname;
        }
        function onUserNicknameChanged() {
            loginUserInfo.text = "用户账号:" + root.loginUser.userPhone + "\n用户密码:" + root.loginUser.userPassword + "\n用户部门:" + root.loginUser.userDepartment + "\n用户医院:" + root.loginUser.userHospital + "\n用户昵称:" + root.loginUser.userNickname;
        }
    }

    TapHandler {
        onTapped: {
            root.forceActiveFocus();
        }
    }

    Grid {
        anchors.fill: parent
        columns: 4
        spacing: 10
        rows: 2

        Item {
            width: (root.width - 30) / 4
            height: (parent.height - 10) / 2

            MaterialTextField {
                width: parent.width
                placeholderText: "手机账号"
                anchors.centerIn: parent
                inputMethodHints: Qt.ImhDigitsOnly
                validator: RegularExpressionValidator {
                    regularExpression: /^1[3-9]\d{9}$/
                }
                onTextChanged: {
                    root.loginUser.userPhone = text;
                }
            }

            MaterialButton {
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: "获取验证码"
                onClicked: {
                    var phone = root.loginUser.userPhone.trim();
                    // 中国大陆手机号：1 开头，第二位 3-9，共 11 位
                    var re = /^1[3-9]\d{9}$/;
                    if (!re.test(phone)) {
                        root.loginUser.userPhone = "手机格式错误";
                        return;
                    }
                    LoginManager.getCaptcha(root.loginUser.userPhone);
                }
            }
        }

        Item {
            width: (root.width - 30) / 4
            height: (parent.height - 10) / 2

            Column {
                height: parent.height * 0.7
                width: parent.width
                anchors.centerIn: parent
                spacing: 30

                MaterialTextField {
                    width: parent.width
                    placeholderText: "部门"
                    onTextChanged: {
                        root.loginUser.userDepartment = text;
                    }
                }

                MaterialTextField {
                    width: parent.width
                    placeholderText: "医院"
                    onTextChanged: {
                        root.loginUser.userHospital = text;
                    }
                }

                MaterialTextField {
                    width: parent.width
                    placeholderText: "昵称"
                    onTextChanged: {
                        root.loginUser.userNickname = text;
                    }
                }
            }
        }

        Item {
            width: (root.width - 30) / 4
            height: (parent.height - 10) / 2

            Column {
                anchors.fill: parent
                spacing: 30

                MaterialTextField {
                    width: parent.width
                    placeholderText: "手机账号"
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: RegularExpressionValidator {
                        regularExpression: /^1[3-9]\d{9}$/
                    }
                    onTextChanged: {
                        root.loginUser.userPhone = text;
                    }
                }

                MaterialTextField {
                    width: parent.width
                    placeholderText: "密码"
                    onTextChanged: {
                        root.loginUser.userPassword = text;
                    }
                }

                MaterialButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "登录"
                    onClicked: {
                        LoginManager.login(root.loginUser.userPhone, root.loginUser.userPassword);
                    }
                }
            }
        }

        Item {
            width: (root.width - 30) / 4
            height: (parent.height - 10) / 2

            Column {
                anchors.fill: parent
                spacing: 30

                MaterialTextField {
                    width: parent.width
                    placeholderText: "手机账号"
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: RegularExpressionValidator {
                        regularExpression: /^1[3-9]\d{9}$/
                    }
                    onTextChanged: {
                        root.loginUser.userPhone = text;
                    }
                }

                MaterialTextField {
                    width: parent.width
                    placeholderText: "密码"
                    onTextChanged: {
                        root.loginUser.userPassword = text;
                    }
                }

                MaterialButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "修改密码"
                    onClicked: {
                        LoginManager.revisePassword(root.loginUser.userPhone, root.loginUser.userPassword);
                    }
                }
            }
        }

        Item {
            width: (root.width - 30) / 4
            height: (parent.height - 10) / 2

            TextArea {
                id: loginUserInfo
                readOnly: true
                wrapMode: TextArea.WrapAnywhere
                font.pixelSize: 12
                width: parent.width
                height: parent.height * 0.8
                clip: true
            }

            MaterialButton {
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: "注册"
                onClicked: {
                    LoginManager.registration(root.loginUser);
                }

                Rectangle {
                    anchors.left: parent.right
                    anchors.leftMargin: 30
                    anchors.verticalCenter: parent.verticalCenter
                    width: 24
                    height: 24
                    radius: 12
                    color: "gray"
                }
            }
        }
    }
}
