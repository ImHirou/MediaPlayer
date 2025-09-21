import QtQuick
import QtQuick.Controls
import QtMultimedia

ApplicationWindow {
    property int currentIndex: -1
    visible:    true
    color:      config.backgroundColor1

    MediaPlayer {
        id: audioPlayer

        property bool repeat: false

        audioOutput: AudioOutput {
            volume: 1
        }

        onRepeatChanged: {
            if (repeat) audioPlayer.loops = MediaPlayer.Infinite
            else audioPlayer.loops = 1
        }

        onMediaStatusChanged: {
            if (mediaStatus == MediaPlayer.EndOfMedia)
                playTrack(currentIndex+1)
        }
    }

    Button {
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
        width: 80
        height: 80
        onClicked: audioPlayer.repeat = !audioPlayer.repeat
    }

    Rectangle {
        id: trackListBackground
        anchors {
            top:        parent.top
            left:       parent.left
            bottom:     parent.bottom
            margins:    16
        }
        border {
            color: config.borderColor
            width: 2
        }
        width:  320 
        color:  config.backgroundColor2
        x:      16
        y:      16
        radius: 8

        ListView {
            id:                 trackListView
            clip:               true 
            anchors.fill:       parent
            anchors.margins:    8

            model:              trackModel 
            delegate:           TrackComponent {}
            focus:              true
        }
    }

    TrackPanel {
        id: panel
        anchors {
            centerIn: parent
        }
        icon: ""
        enabled: false
    }

    Button {
        id: cfgReload
        anchors {
            bottom: parent.bottom
            right: parent.right
            margins: 24
        }
        width: 240
        height: 48
        onClicked: {
            config.reloadConfig();
        }
    }

    function playTrack(index) {
        if (index == currentIndex) return
        if (index < 0) currentIndex = trackModel.count() - 1
        else if (index >= trackModel.count()) currentIndex = 0
        else currentIndex = index
        let track = trackModel.get(currentIndex)
        audioPlayer.source = "file://" + track.path
        panel.icon = track.icon
        panel.enabled = true
        audioPlayer.play()
    }

}

