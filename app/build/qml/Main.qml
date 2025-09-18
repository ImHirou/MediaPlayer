import QtQuick 2.15
import QtQuick.Controls 2.15
import QtMultimedia 5.15

ApplicationWindow {
    visible:    true
    color:      "#f1f1f1"

    Rectangle {
        anchors {
            top:        parent.top
            left:       parent.left
            bottom:     parent.bottom
            margins:    16
        }
        width:  320 
        color:  "#2a2a2a"
        x:      16
        y:      16
        
        Component {
            id: trackDelegate
            Item {
                id:                         trackItem
                required property string    name
                required property string    artist
                required property url       icon
                width:                      ListView.view.width 
                implicitHeight:             column.implicitHeight + 10
                Rectangle {
                    anchors {
                        top:        parent.top
                        left:       parent.left
                        margins:    4
                    }
                    width: 304
                    color: "#1a1a1a"
                    Image {
                        anchors {
                            top:    0
                            left:   0
                        }
                        source:     trackItem.icon
                        cache:      true
                        width:      128
                        height:     128
                        fillMode:   Image.PreserveAspectFit
                    }
                    Text {
                        anchors {
                            top:    parent.top
                            right:  parent.right
                        }
                        text: trackItem.name
                    }
                    Text {
                        anchors {
                            bottom: parent.bottom
                            right:  parent.right
                        }
                        text: trackItem.artist
                    }
                }
            }
        }
        
        ListView {
            clip:               true 
            anchors.fill:       parent
            anchors.margins:    8

            model:              trackModel 
            delegate:           trackDelegate
            focus:              true
        }
    }

}
