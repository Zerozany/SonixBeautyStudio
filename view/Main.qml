import QtQuick
import QZeroSystem
import QZeroZanyUI
import QtQuick.Controls

ZeroWindow {
    id: mainWindow
    color: mainWindow.backgroundColor

    readonly property string backgroundColor: ThemeManager.currentTheme["backgroundColor"]

    StackView {
        id: mainStackView
        anchors.fill: parent
        initialItem: LoginPage {}
    }

    DynamicIsland {
        visible: !mainStackView.currentItem instanceof LoginPage
    }

    ShortcutControl {
        sequences: [StandardKey.Back]
        onAndroidEvent: {
            StackViewControl.stackPop();
        }
    }

    Component.onCompleted: {}
}
