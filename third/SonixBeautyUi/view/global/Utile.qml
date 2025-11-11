pragma Singleton
import QtQuick.Window
import QtQuick

QtObject {

    function showApplicationTip(_window, _text, _interval = 2000) {
        if (!_window) {
            console.error("[Utile] showApplicationTip(): window is null");
            return;
        }
        const tipComp = Qt.createComponent("../content/ApplicationTip.qml");
        if (tipComp.status === Component.Ready) {
            const tipObj = tipComp.createObject(_window, {
                window: _window,
                text: _text,
                interval: _interval
            });
            if (tipObj === null) {
                console.error("[Utile] showApplicationTip(): create ApplicationTip failed");
            }
        } else if (tipComp.status === Component.Error) {
            console.error("[Utile] showApplicationTip(): Component loading failed:", tipComp.errorString());
        }
    }
}
