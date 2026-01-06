import QtQuick
// import QtQuick.Controls
import QZeroSystem
import QZeroZanyUI

ZeroWindow {
    id: mainWindow
    color: mainWindow.backgroundColor

    readonly property string backgroundColor: ThemeManager.currentTheme["backgroundColor"]

    // StackView {
    //     id: mainStackView
    //     anchors.fill: parent
    //     initialItem: LoginPage {}
    // }

    LineTextField {
        x: 50
        y: 50
        width: 300
        height: 50
        placeText: "邮箱"
        source: "qrc:/view/resource/setting.png"
        passwordSource: "qrc:/view/resource/settingPressed.png"
        passwordPressedSource: "qrc:/view/resource/setting.png"
        clearSource: "qrc:/view/resource/clearInput.png"
        fontBold: true
        password: true
    }

    NormalButton {
        x: 100
        y: 300
        width: 120
        height: 60
        text: "CCC"
    }

    Component.onCompleted: {}
}
