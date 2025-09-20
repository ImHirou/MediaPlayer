import QtQuick
import QtQuick.Controls

Item {
    anchors {
        horizontalCenter: parent.horizontalCenter
        bottom: parent.bottom
        margins: 32
    }
    width: 40
    height: 40

    Rectangle {
        id: button
        anchors.fill: parent
        color: config.primaryColor
        radius: width / 2
        
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                let dx = mouse.x - button.width / 2
                let dy = mouse.y - button.height / 2
                if (dx*dx + dy*dy <= Math.pow(button.width/2, 2)) {
                    if (audioPlayer.playing) audioPlayer.pause()
                    else audioPlayer.play()
                }
            }

            onPositionChanged: {
                let dx = mouse.x - button.width / 2
                let dy = mouse.y - button.height / 2
                if (dx*dx + dy*dy <= Math.pow(button.width/2, 2)) {
                    button.color = config.primaryHoverColor
                } else {
                    button.color = config.primaryColor
                }
            }

            onExited: button.color = config.primaryColor
        }
    }
}
