import QtQuick
import QZeroZanyUI
import QtQuick.Controls

Rectangle {
    id: root
    color: "red"

    Connections {
        target: StackViewControl
        function onStackPop() {
            root.StackView.view.pop();
        }
    }
}
