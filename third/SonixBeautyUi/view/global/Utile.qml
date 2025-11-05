pragma Singleton
import QtQuick.Window
import QtQuick

QtObject {
    property var mainWindowObject

    function showApplicationTip(_window, _text, _interval = 2000) {
        if (!_window) {
            console.error("[Utile] showApplicationTip(): window is null");
            return;
        }
        const component = Qt.createComponent("../content/ApplicationTip.qml");
        if (component.status === Component.Ready) {
            const tip = component.createObject(_window, {
                window: _window,
                text: _text,
                interval: _interval
            });
            if (tip === null) {
                console.error("[Utile] create ApplicationTip failed");
            }
        } else if (component.status === Component.Error) {
            console.error("[Utile] Component loading failed:", component.errorString());
        }
    }
}
