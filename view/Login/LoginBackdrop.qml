import QtQuick
import QZeroMaterialUI
import SonixBeautyStudio

Rectangle {
    id: root
    gradient: GradientStyle {}

    readonly property url logoSource: "qrc:/qt/qml/SonixBeautyStudio/view/resource/logo.png"

    Image {
        width: implicitWidth
        height: implicitHeight
        anchors.top: parent.top
        anchors.topMargin: ContentConf.landScape ? parent.height * 0.20 : parent.height * 0.30
        anchors.horizontalCenter: parent.horizontalCenter
        source: root.logoSource
    }
}
