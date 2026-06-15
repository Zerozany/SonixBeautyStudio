import QtQuick
import QZeroSystem
import QZeroMaterialUI

ZeroWindow {
    id: mainWindow

    MainStackLayout {
        anchors.fill: parent
        initialItem: App {}
    }

    ShortcutControl {
        sequences: [StandardKey.Back]
        onAndroidEvent: {
            MainSignals.popStack();
        }
    }

    Component.onCompleted: {}
}
