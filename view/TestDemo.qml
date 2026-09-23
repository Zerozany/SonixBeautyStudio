import QtQuick
import QtQuick.Controls
import QZeroMaterialUI

Item {
    id: root

    Grid {
        anchors.fill: parent
        columns: 4        // 关键：必须指定列数
        spacing: 10          // 间距
        rows: 2

        Item {
            width: (root.width - 30) / 4      // 减去 spacing
            height: root.height / 2
            ListView {
                width: parent.width
                height: parent.height * 0.8
                anchors.top: parent.top
                model: DevicesManager.devicesList
                delegate: Text {
                    required property var modelData
                    text: modelData.ssid + ":" + modelData.level
                }
            }

            Connections {
                target: DevicesManager
                function onDevicesListChanged() {
                    if (DevicesManager.devicesList.length === 0) {
                        updateBtn.text = "刷新频率过高";
                    } else {
                        updateBtn.text = "刷新";
                    }
                // for (var i = 0; i < DevicesManager.devicesList.length; ++i) {
                //     var item = DevicesManager.devicesList[i];
                //     console.log(item.ssid, item.level);
                // }
                }
            }

            MaterialButton {
                id: updateBtn
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: "刷新"
                onClicked: {
                    DevicesManager.refreshDevicesList();
                }
            }
        }

        Item {
            width: (root.width - 30) / 4
            height: root.height / 2

            Column {
                width: parent.width
                height: parent.height * 0.5
                anchors.centerIn: parent
                Label {
                    id: currentWifiLabel
                    width: parent.width
                    height: parent.height * 0.4
                }

                Label {
                    id: currentWifiSignalQualityLabel
                    width: parent.width
                    height: parent.height * 0.4
                }
            }

            MaterialButton {
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: "刷新"
                onClicked: {
                    currentWifiLabel.text = "当前wifi:" + DevicesManager.currentWifiName();
                    currentWifiSignalQualityLabel.text = "当前信号强度:" + DevicesManager.currentWifiSignalQuality();
                }
            }
        }

        Item {
            width: (root.width - 30) / 4      // 减去 spacing
            height: root.height / 2

            TapHandler {
                onTapped: {
                    parent.forceActiveFocus();
                }
            }

            MaterialTextField {
                id: phoneTextField
                width: parent.width
                placeholderText: "手机账号"
                anchors.centerIn: parent
                inputMethodHints: Qt.ImhDigitsOnly
                validator: RegularExpressionValidator {
                    regularExpression: /^1[3-9]\d{9}$/
                }
            }

            MaterialButton {
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: "获取"
                onClicked: {
                    var phone = phoneTextField.text.trim();
                    // 中国大陆手机号：1 开头，第二位 3-9，共 11 位
                    var re = /^1[3-9]\d{9}$/;
                    if (!re.test(phone)) {
                        phoneTextField.text = "手机格式错误";
                        return;
                    }
                    LoginManager.getCaptcha(phoneTextField.text);
                }
            }
        }

        Item {
            width: (root.width - 30) / 4      // 减去 spacing
            height: root.height / 2

            TapHandler {
                onTapped: {
                    parent.forceActiveFocus();
                }
            }

            Column {
                width: parent.width * 0.9
                height: parent.height * 0.9
                anchors.centerIn: parent
                spacing: 20

                MaterialTextField {
                    id: wifiField
                    width: parent.width
                    placeholderText: "Wifi名称"
                    text: "US06-9C50D101E3B4"
                }
                MaterialTextField {
                    id: passwordField
                    width: parent.width
                    placeholderText: "Wifi密码"
                    text: "12345678"
                }

                MaterialButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "连接"
                    onClicked: {
                        DevicesManager.connectToWifi(wifiField.text, passwordField.text);
                    }
                }

                MaterialButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "断开"
                    onClicked: {
                        DevicesManager.disconnectWifi();
                    }
                }
            }
        }

        //
        Item {
            width: (root.width - 30) / 4      // 减去 spacing
            height: root.height / 2

            Column {
                width: parent.width
                height: parent.height * 0.9
                anchors.centerIn: parent
                spacing: 20

                Connections {
                    target: QmlDebug
                    function onSendDataChanged() {
                        cmdArea.append(QmlDebug.sendData);
                    }
                }

                MaterialButton {
                    width: parent.width / 2
                    text: "发送数据"
                    anchors.horizontalCenter: parent.horizontalCenter
                    onClicked: {
                        QmlDebug.sendDatas();
                    }
                }

                TextArea {
                    id: cmdArea
                    readOnly: true
                    width: parent.width
                    height: parent.height * 0.8
                    font.pixelSize: 8
                }
            }
        }
    }
}
