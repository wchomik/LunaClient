import QtQuick 2.14

Rectangle {
    id: root
    width: 20
    height: 20
    color: "magenta"


    transform: Translate {
        x: -root.width / 2
        y: -root.height / 2
    }
    MouseArea {
        anchors.fill: parent
        drag {
            target: root
            threshold: 0
            axis: Drag.XAndYAxis
        }
    }
}
