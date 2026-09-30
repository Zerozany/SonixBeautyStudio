import QtQuick
import SonixBeautyStudio
import QZeroMaterialUI
import QtQuick.Controls

Item {
    id: root

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

            MaterialButton {
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
            height: (parent.height - 10) / 2

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
            width: (root.width - 30) / 4
            height: (parent.height - 10) / 2

            Column {
                width: parent.width
                height: parent.height * 0.9
                anchors.centerIn: parent
                spacing: 20

                MaterialTextField {
                    id: wifiField
                    width: parent.width
                    placeholderText: "Wifi名称"
                    text: "US06-9C50D101E180"
                    // text: "ChinaNet-zero821"
                }
                MaterialTextField {
                    id: passwordField
                    width: parent.width
                    placeholderText: "Wifi密码"
                    text: "12345678"
                    // text: "18583943303"
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

        Item {
            width: (root.width - 30) / 4
            height: (parent.height - 10) / 2

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

                TextArea {
                    id: cmdArea
                    readOnly: true
                    width: parent.width
                    height: parent.height * 0.9
                    font.pixelSize: 8
                }

                MaterialButton {
                    width: parent.width / 2
                    text: "发送数据"
                    anchors.horizontalCenter: parent.horizontalCenter
                    onClicked: {
                        QmlDebug.sendDatas();
                    }
                }
            }
        }

        Item {
            width: (root.width - 30) / 4
            height: (parent.height - 10) / 2

            Column {
                width: parent.width
                height: parent.height * 0.9
                anchors.centerIn: parent
                spacing: 20

                Connections {
                    target: QmlDebug
                    function onRecvDataChanged() {
                        recvAream.text = QmlDebug.recvData;
                    }
                }

                TextArea {
                    id: recvAream
                    readOnly: true
                    wrapMode: TextArea.WrapAnywhere
                    font.pixelSize: 10
                    width: parent.width
                    height: parent.height * 0.9
                    clip: true
                }

                Label {
                    width: parent.width / 2
                    text: "接收数据"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
    }
}
