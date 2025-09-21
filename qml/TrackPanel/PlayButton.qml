import QtQuick
import QtQuick.Controls
import app

Item {
    anchors {
        horizontalCenter: parent.horizontalCenter
        bottom: parent.bottom
        margins: 32
    }
    width: 40
    height: 40
    CircleButton {
        id: button
        anchors.fill: parent
        onClicked: {
            if (audioPlayer.playing) audioPlayer.pause()
            else audioPlayer.play()
        }
    }
}
