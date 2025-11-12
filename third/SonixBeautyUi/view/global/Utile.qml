pragma Singleton
import QtQuick.Window
import QtQuick

QtObject {

    function showApplicationTip(_window: var, _text: string, _interval: int) {
        if (!_window) {
            console.error("[Utile] showApplicationTip(): window is null");
            return;
        }
        if (!_interval) {
            _interval = 2000;
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
