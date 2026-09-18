import QtQuick
// import QtQuick.Controls
import QZeroSystem
import QZeroMaterialUI

// import SonixBeautyStudio

// import QtMultimedia

ZeroWindow {
    id: mainWindow

    // StackView {
    //     anchors.fill: parent
    //     initialItem: App {}
    // }

    // CaptureMedia {
    //     id: captureMedia
    //     screenCapture.active: true
    //     recorder.outputLocation: "/storage/emulated/0/Android/data/org.qtproject.SonixBeauty/files/Movies"
    // }

    // Button {
    //     anchors.centerIn: parent
    //     text: captureMedia.recorder.recorderState === MediaRecorder.RecordingState ? "停止" : "录制"
    //     onClicked: {
    //         if (captureMedia.recorder.recorderState === MediaRecorder.RecordingState) {
    //             captureMedia.recorder.stop();
    //         } else {
    //             captureMedia.recorder.record();
    //         }
    //     }
    // }

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
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
        text: "刷新"
        onClicked: {
            // LoginManager.getCaptcha();
            // console.log(LoginManager.host);
            // console.log(LoginManager.port);
            DevicesManager.refreshDevicesList();
        }
    }

    ListView {
        anchors.centerIn: parent
        width: parent.width * 0.5
        height: parent.height * 0.7
        model: DevicesManager.devicesList
        delegate: Text {
            required property var modelData
            text: modelData.ssid + ":" + modelData.level
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    ShortcutControl {
        sequences: [StandardKey.Back]
        onAndroidEvent: {}
    }

    Component.onCompleted: {
        // MainAlias
    }
}
