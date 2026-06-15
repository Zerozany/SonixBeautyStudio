import QtQuick
import QtQuick.Controls

StackView {
    id: root

    Connections {
        target: MainSignals

        function onPushStack(_stackPage) {
            root.push(_stackPage);
        }

        function onReplaceStack(_stackPage) {
            root.replace(_stackPage);
        }

        function onPopStack() {
            root.pop();
        }
    }
}
