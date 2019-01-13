import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

ColumnLayout {
    Settings {
        category: "Light"
//        property alias color: colorDialog.color
    }

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
                var sum = X + 1 + Z;
                Model.cieXYZ(X / sum, 1 / sum, Z / sum);
                mouse.accepted = true;
            }

            onPositionChanged: setXYZ(mouse)
            onPressed: setXYZ(mouse)
        }
    }
}
