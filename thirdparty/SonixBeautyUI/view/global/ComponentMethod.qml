pragma Singleton
import QtQuick

QtObject {

    function showApplicationTip(_parentItem: var, _text: var, _interval: int): var {
        var component = Qt.createComponent("../content/ApplicationTip.qml");
        if (component.status === Component.Ready) {
            var tip = component.createObject(_parentItem, {
                text: _text || "",
                interval: _interval || 2000
            });
            if (tip === null) {
                console.error("Failed to create ApplicationTip object");
                return null;
            }
            return tip;
        } else if (component.status === Component.Error) {
            console.error("Error loading ApplicationTip.qml");
            return null;
        }
    }
}
