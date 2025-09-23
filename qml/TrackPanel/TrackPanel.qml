import QtQuick
import QtQuick.Controls
import app

Item {
    id: panel
    required property url icon

    property real sSize: Math.min(parent.width / 2, parent.height / 2);
    width: sSize
    height: sSize
    Rectangle {
        anchors.fill:   parent
        id:             background
        color:          config.backgroundColor2
        radius:         16

        Image {
            anchors {
                top:                parent.top
                horizontalCenter:   parent.horizontalCenter
                bottom:             parent.verticalCenter
                margins:            24
            }
            source:     panel.icon
            cache:      false
            smooth:     true
            fillMode:   Image.PreserveAspectFit
        }

        Slider {
            id: volumeSlider
            anchors {
                right:      parent.right
                top:        parent.top
                bottom:     parent.verticalCenter
                margins:    8
            }
            orientation: Qt.Vertical
            from:   0.
            to:     1.
            value:  config.volume
            onMoved: {
                config.volume = volumeSlider.value
                audioPlayer.audioOutput.volume = volumeSlider.value
            }
            onPressedChanged: {
                if (!pressed) config.writeFile(true)
            }
        }
        BetterSlider {
            id: positionSlider
            anchors {
                horizontalCenter:   parent.horizontalCenter
                verticalCenter:     parent.verticalCenter
            }
            height: 16
            width:  200
            from:   0
            to:     audioPlayer.duration
            live:   false
            
            onPressedChanged:
                if(!pressed) audioPlayer.position = positionSlider.value

            Connections {
                target: audioPlayer
                onDurationChanged: {
                    positionSlider.to = audioPlayer.duration
                }
                onPositionChanged: {
                    if (!positionSlider.pressed) 
                        positionSlider.value = audioPlayer.position
                }
            }
        }

        NextButton {
            id: nextButton
        }

        PreviousButton {
            id: previousButton
        }

        PlayButton {
            id: playButton
        }
    }
}
