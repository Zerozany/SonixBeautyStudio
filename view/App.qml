import QtQuick
import "HomePage"
import SonixBeautyUI

Item {
    id: root

    property alias backgroundColor: homePage.backgroundColor

    readonly property int appTopMargin: 25
    readonly property int appbottomMargin: 15

    Rectangle {
        anchors.fill: parent
        anchors.topMargin: root.appTopMargin
        anchors.bottomMargin: root.appbottomMargin
        color: root.backgroundColor

        HomePage {
            id: homePage
            anchors.fill: parent
        }
    }

    Component.onCompleted: {
        Utile.showApplicationTip(Utile.mainWindowObject, qsTr("你好 世界"));
    }
}
