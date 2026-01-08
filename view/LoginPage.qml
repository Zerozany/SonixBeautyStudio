import QtQuick
import QZeroZanyUI

Rectangle {
    id: root
    color: root.backgroundColor

    readonly property string backgroundColor: "#7FFFD4"
    readonly property url logoSource: "qrc:/view/resource/SonixBeautyLogo.png"

    Image {
        anchors.top: parent.top
        anchors.topMargin: ComponentConf.landScape ? parent.height * 0.10 : parent.height * 0.20
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.Pad
        source: root.logoSource
    }
}
