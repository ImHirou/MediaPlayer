import QtQuick
import QtQuick.Controls


Item {
    id: root
    property color backgroundColor: config.backgroundColor3
    property color mainColor: config.primaryColor

    signal moved()

    Slider {
        id: slider
        anchors.fill: parent
        from: root.from
        to: root.to
        value: root.value
        live: root.live 
        orientation: root.orientation

        onMoved: root.moved

        handle: Rectangle { width: 0; height: 0 }

        background: Rectangle {
            anchors.fill: parent
            implicitHeight: 6
            implicitWidth: 6
            radius: (root.orientation === Qt.Horizontal ? height/2 : width/2)
            color: root.backgroundColor
            Rectangle {
                anchors.fill: parent
                width: (root.orientation === Qt.Horizontal ? parent.width * slider.position : parent.width)
                height: (root.orientation === Qt.Horizontal ? parent.height : parent.height * slider.position)
                radius: parent.radius
                color: root.mainColor
            }
        }
    }

    property alias orientation: slider.orientation
    property alias live: slider.live
    property alias value: slider.value
    property alias from: slider.from
    property alias to: slider.to
    property alias pressed: slider.pressed
}

