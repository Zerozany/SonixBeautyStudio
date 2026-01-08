import QtQuick
import QtQuick.Controls
import QZeroSystem
import QZeroZanyUI

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

    Shortcut {
        sequences: [StandardKey.Back]
        onActivated: {
            if (mainStackView.depth >= 1) {
                mainStackView.pop();
            } else {
                Qt.quit();
            }
        }
    }

    Component.onCompleted: {}
}
