import QtQuick
import QtQuick.Controls
import QZeroSystem
import QZeroMaterialUI

ZeroWindow {
    id: mainWindow

    StackView {
        anchors.fill: parent
        initialItem: App {}
    }

    ShortcutControl {
        sequences: [StandardKey.Back]
        onAndroidEvent: {}
    }

    Component.onCompleted: {
        // MainAlias
    }
}
