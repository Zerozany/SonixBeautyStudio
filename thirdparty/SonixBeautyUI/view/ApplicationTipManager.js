// ApplicationTipManager.js

function showApplicationTip(parentItem, text, interval) {
    var component = Qt.createComponent("qrc:/qt/qml/SonixBeautyUI/view/content/ApplicationTip.qml");
    if (component.status === Component.Ready) {
        var tip = component.createObject(parentItem, {
            text: text || "",
            interval: interval || 2000
        });
        if (tip === null) {
            console.error("Failed to create ApplicationTip object");
            return null;
        }
        return tip;
    } else if (component.status === Component.Error) {
        console.error("Error loading ApplicationTip.qml:", component.errorString());
        return null;
    }
    return null;
}
