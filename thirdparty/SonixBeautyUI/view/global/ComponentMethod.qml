pragma Singleton
import QtQuick

QtObject {

    // 获取顶层窗口对象
    function findTopLevelWindow(_item) {
        while (_item.parent) {
            _item = _item.parent;
        }
        return _item;
    }

    // 全局提示气泡
    function showApplicationTip(_parentItem: var, _text: var, _interval: int): var {
        var obj = Qt.createComponent("qrc:/qt/qml/SonixBeautyUI/view/content/ApplicationTip.qml");
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
