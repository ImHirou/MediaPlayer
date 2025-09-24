import QtQuick
import QtQuick.Controls
import app

Item {
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
