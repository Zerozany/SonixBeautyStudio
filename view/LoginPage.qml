import QtQuick
import QtQuick.Layouts
import QZeroZanyUI

Rectangle {
    id: root
    color: root.backgroundColor

    readonly property string backgroundColor: "#7FFFD4"
    readonly property url logoSource: "qrc:/view/resource/SonixBeautyLogo.png"
    readonly property string elementColor: ThemeManager.currentTheme["elementColor"]
    readonly property int elementRadius: ElementStyle.elementRadius * 2

    ColumnLayout {
        anchors.fill: parent

        Image {
            Layout.topMargin: ComponentConf.landScape ? parent.height * 0.10 : parent.height * 0.20
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            fillMode: Image.Pad
            source: root.logoSource
        }

        Rectangle {
            color: root.elementColor
            radius: root.elementRadius
            Layout.preferredWidth: parent.width * 0.5
            Layout.preferredHeight: parent.height * 0.4
            Layout.alignment: Qt.AlignCenter | Qt.AlignTop

            StackLayout {
                anchors.fill: parent
            }
        }
    }
}
