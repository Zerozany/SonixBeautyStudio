pragma Singleton
import QtQuick

QtObject {

    function showApplicationTip(_parentItem: var, _text: var, _interval: int): var {
        var obj = Qt.createComponent("../content/ApplicationTip.qml");
        if (obj.status === Component.Ready) {
            obj.createObject(_parentItem, {
                text: _text || "",
                interval: _interval || 2000
            });
        } else if (obj.status === Component.Error) {
            console.error("Error loading ApplicationTip.qml");
        }
    }
}
