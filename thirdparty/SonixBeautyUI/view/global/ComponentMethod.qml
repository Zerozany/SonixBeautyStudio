pragma Singleton
import QtQuick

QtObject {

    function showApplicationTip(_parentWindow: var, _text: string, _interval = 2000) {
        if (!_parentWindow) {
            console.error("[Utile] showApplicationTip(): window is null");
            return;
        }
        const tipComp = Qt.createComponent("../content/ApplicationTip.qml");
        if (tipComp.status === Component.Ready) {
            const tipObj = tipComp.createObject(_parentWindow, {
                parentWindow: _parentWindow,
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
