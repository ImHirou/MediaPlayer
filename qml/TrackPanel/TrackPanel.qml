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
            id: image
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

        VerticalSlider {
            id: volumeSlider
            anchors {
                right:      parent.right
                top:        image.top
                bottom:     image.bottom
                rightMargin:    12
            }
            width: 16
            height: 200
            from:   0.
            to:     1.
            value:  config.volume
            live: false
            onMoved: {
                config.volume = volumeSlider.value
                audioPlayer.audioOutput.volume = volumeSlider.value
            }
            onPressedChanged: {
                if (!pressed) config.writeFile(true)
            }
        }
        HorizontalSlider {
            id: positionSlider
            anchors {
                top: image.bottom
                horizontalCenter: parent.horizontalCenter
                margins: 12
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

        Rectangle {
            id: repeatButton
            anchors {
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
                margins: 8
            }
            width: 32
            height: 32
            radius: 8
            color: config.backgroundColor3

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                Connections {
                    onClicked: {
                        audioPlayer.repeat = !audioPlayer.repeat
                    }
                    onEntered: repeatButton.color = config.primaryHoverColor
                    onExited: {
                        repeatButton.color = audioPlayer.repeat ? config.primaryColor : config.backgroundColor3
                    }
                }
            }
        }

        Text {
            id: trackTime
            anchors {
                top: positionSlider.bottom
                horizontalCenter: positionSlider.horizontalCenter
                margins: 8
            }
            color: config.secondaryTextColor
            text: {
                var minutes = Math.floor(audioPlayer.duration / 60000);
                var seconds = Math.floor((audioPlayer.duration / 1000) % 60);
                return minutes + ":" + (seconds < 10 ? "0" + seconds : seconds);
            }
            Connections {
                target: audioPlayer
                onDurationChanged: {
                    var minutes = Math.floor(audioPlayer.duration / 60000);
                    var seconds = Math.floor((audioPlayer.duration / 1000) % 60);
                    trackTime.text = minutes + ":" + (seconds < 10 ? "0" + seconds : seconds);
                }
            }
        }

        NextButton {
            id: nextButton
            anchors {
                bottom:     repeatButton.top
                right:      parent.right
                margins:    16
            }
        }

        PreviousButton {
            id: previousButton
            anchors {
                bottom:     repeatButton.top
                left:       parent.left
                margins:    16
            }
        }

        PlayButton {
            id: playButton
            anchors {
                horizontalCenter:   parent.horizontalCenter
                bottom:             repeatButton.top
                margins:            16
            }
        }
    }
}
