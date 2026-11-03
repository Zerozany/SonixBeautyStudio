import QtQuick
import QZeroMaterialUI

Rectangle {
    id: root

    color: "#F5F5F5"

    // ---- 测量线段容器：本身不吃事件，子项只有顶点吃事件 ----
    Item {
        anchors.fill: parent
        z: 10   // 盖在图像上面

        Line {
            anchors.fill: parent
            unit: "mm"
            ratio: 2.0
        }

        Line {
            anchors.fill: parent
            unit: "mm"
            ratio: 1.5
        }

        Line {
            anchors.fill: parent
            unit: "mm"
        }
    }
}
