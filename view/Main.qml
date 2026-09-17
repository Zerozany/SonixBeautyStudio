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

    MaterialButton {
        anchors.centerIn: parent
        onClicked: {
            LoginManager.getCaptcha();
            console.log(LoginManager.host);
            console.log(LoginManager.port);
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
