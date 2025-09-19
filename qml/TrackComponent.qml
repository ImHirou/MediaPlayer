import QtQuick
import QtQuick.Controls

    Item {
        id: item
        required property int       index
        required property string    name
        required property string    artist
        required property url       icon
        required property string    path
        width: ListView.view.width
        Row {
            id: row
            spacing: 4
            anchors.fill: parent

            Rectangle {
                id:     background
                width:  parent.width
                height: 144
                color:  config.backgroundColor2
                radius: 8
                border {
                    color: config.borderColor
                    width: 2
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        playTrack(index)
                    }
                    onEntered: {
                        background.color = config.backgroundColor3
                    }
                    onExited: {
                        background.color = config.backgroundColor2
                    }
                }

                Image {
                    anchors {
                        top:        parent.top
                        left:       parent.left
                        margins:    8
                    }
                    width:  128
                    height: 128
                    source: item.icon
                    cache: true
                    smooth: true
                    fillMode: Image.PreserveAspectFit
                }

                Text {
                    anchors {
                        top:        parent.top
                        right:      parent.right
                        margins:    8
                    }
                    font.pixelSize: 20
                    width: 200
                    wrapMode: Text.Wrap
                    horizontalAlignment: Text.AlignRight
                    color: config.mainTextColor
                    text: item.name
                }

                Text {
                    anchors {
                        right:      parent.right
                        bottom:     parent.bottom
                        margins:    8
                    }
                    font.pixelSize: 20
                    width: 200
                    wrapMode: Text.Wrap
                    horizontalAlignment: Text.AlignRight
                    color: config.secondaryTextColor
                    text: item.artist
                }
            }
        }
        implicitHeight: row.implicitHeight + 10
    }
