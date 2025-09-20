import QtQuick
import QtQuick.Controls

Item {
    id: root

    property color defaultColor:    config.primaryColor
    property color hoverColor:      config.primaryHoverColor
    signal clicked()
   
    Rectangle {
        id: button
        anchors.fill: parent
        color: root.defaultColor
        radius: width / 2
        
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                let dx = mouse.x - button.width / 2
                let dy = mouse.y - button.width / 2
                if (dx*dx + dy*dy <= Math.pow(button.width/2, 2))
                    root.clicked()
            }
            
            onPositionChanged: {
                let dx = mouse.x - button.width / 2
                let dy = mouse.y - button.width / 2
                if (dx*dx + dy*dy <= Math.pow(button.width/2, 2))
                    button.color = root.hoverColor
                else
                    button.color = root.defaultColor
            }
            
            onExited: button.color = root.defaultColor
        }
    }
}
