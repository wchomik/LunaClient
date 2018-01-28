import QtQuick 2.6
import QtQuick.Window 2.2

import MyStuff 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "black"

    UdpServer {
        id: server
    }

    Strand {
        id: leftStrand
        model: server.leftPixels().data
    }

    Strand {
        id: rightStrand
        model: server.rightPixels().data
    }

    Component.onCompleted: {
        leftStrand.begin.x = 50
        leftStrand.begin.y = 300

        leftStrand.end.x = 50
        leftStrand.end.y = 50

        rightStrand.begin.x = 500
        rightStrand.begin.y = 300

        rightStrand.end.x = 500
        rightStrand.end.y = 50

        server.listenOnPort(1234)
    }
}
