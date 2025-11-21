import QtQuick
import SonixBeautySystem
import SonixBeautyUI

SonixBeautyWindow {
    id: mainWindow
    color: mainWindow.backgroundColor

    readonly property string backgroundColor: ThemeManager.currentTheme.backgroundColor

    Sidebar {
        edge: topEdge
    }

    Sidebar {
        edge: bottomEdge
    }

    Sidebar {
        edge: leftEdge
    }

    Sidebar {
        edge: rightEdge
    }

    Component.onCompleted: {
        ComponentMethod.showApplicationTip(mainWindow, qsTr("Hello World!"), 2000);
    }
}
