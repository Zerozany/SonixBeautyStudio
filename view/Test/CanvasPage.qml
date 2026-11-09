import QtQuick
import QZeroMaterialUI
import QtQuick.Controls

Rectangle {
    id: root
    color: "#F5F5F5"

    function depthRatio() {
        return slider.value / (slider2.value * 1);
    }

    Slider {
        id: slider
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 50
        anchors.leftMargin: 50

        readonly property real minValue: 24.639999493956566
        readonly property real maxValue: 61.59999966621399

        from: minValue
        to: maxValue
        stepSize: 0.0001
        value: maxValue

        onValueChanged: {
            if (value < minValue)
                value = minValue;
            else if (value > maxValue)
                value = maxValue;
        }

        Text {
            text: "深度因子:" + slider.value
            anchors.left: parent.right
            anchors.leftMargin: 25
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Slider {
        id: slider2
        anchors.top: slider.bottom
        anchors.left: slider.left
        anchors.topMargin: 50

        readonly property real minValue: 1639
        readonly property real maxValue: 2458

        from: minValue
        to: maxValue
        stepSize: 1
        value: minValue

        onValueChanged: {
            if (value < minValue)
                value = minValue;
            else if (value > maxValue)
                value = maxValue;
        }

        Text {
            text: "图像高度:" + slider2.value
            anchors.left: parent.right
            anchors.leftMargin: 25
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Item {
        anchors.fill: parent

        Line {
            anchors.fill: parent
            unit: "mm"
            ratio: root.depthRatio()
        }

        Circle {
            anchors.fill: parent
            ratio: root.depthRatio()
            unit: "px"
        }

        Ellipse {
            anchors.fill: parent
            ratio: root.depthRatio()
        }
    }
}
