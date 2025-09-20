import QtQuick
import QtQuick.Controls
import app

Item {
    width: 40
    height: 40
    anchors {
        bottom: parent.bottom
        right: parent.right
        margins: 32
    }
    CircleButton {
        id: button
        anchors.fill: parent
        onClicked: playTrack(currentIndex+1)
    }
}
