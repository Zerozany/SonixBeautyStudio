import QtQuick

Gradient {
    id: root

    readonly property string colorTop: "#7FFFD4"
    readonly property string colorBottmom: "white"

    orientation: Gradient.Vertical
    GradientStop {
        position: 0.0
        color: root.colorTop
    }
    GradientStop {
        position: 1.0
        color: root.colorBottmom
    }
}
