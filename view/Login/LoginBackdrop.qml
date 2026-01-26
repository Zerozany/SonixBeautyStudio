import QtQuick
import QZeroMaterialUI
import SonixBeautyStudio

Rectangle {
    id: root
    gradient: GradientStyle {}

    readonly property int elementMargins: ElementStyle.elementMargins * 2
    readonly property url logoSource: "qrc:/qt/qml/SonixBeautyStudio/view/resource/logo.png"

    Image {
        anchors.top: parent.top
        anchors.topMargin: ContentConf.landScape ? parent.height * 0.20 : parent.height * 0.30
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.Pad
        source: root.logoSource
    }
}
