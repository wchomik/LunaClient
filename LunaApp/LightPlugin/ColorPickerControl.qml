import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

ColumnLayout {
    Rectangle {
        id: colorButton
        height: 80
        Layout.fillWidth: true
        color: Model.color
        radius: 8
    }

    Image {
        id: img
        source: "qrc:/Light/CIE1931xy.png"
        fillMode: Image.PreserveAspectFit
        Layout.fillWidth: true
        Layout.fillHeight: true
        MouseArea {
            anchors.centerIn: parent
            width: img.paintedWidth
            height: img.paintedHeight
            function setXYZ(mouse) {
                var x = (mouseX / width - 0.12) / 0.83 * 0.8;
                var y = (0.9 - (mouseY / height)) / 0.87 * 0.9;
                var X = x / y;
                var Z = (1 - x - y) / y;
                Model.cieXYZ(X, 1, Z);
                console.log(x, y);
                console.log(X, 1, Z);
                mouse.accepted = true;
            }

            onPositionChanged: setXYZ(mouse)
            onPressed: setXYZ(mouse)
        }
    }
}
