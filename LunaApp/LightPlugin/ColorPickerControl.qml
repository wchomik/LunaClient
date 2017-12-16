import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import Qt.labs.settings 1.0

ColumnLayout {
    Settings {
        category: "Light"
        property alias color: colorDialog.color
    }

    Button {
        text: qsTr("Pick color")
        onClicked: colorDialog.open()
        Layout.fillWidth: true
    }

    Rectangle {
        id: colorButton
        height: 80
        Layout.fillWidth: true
        color: Light.color
        radius: 8
    }

    ColorDialog {
        id: colorDialog
        title: "Choose a color"
        width: 450
        height: 450
        color: Light.color
        onCurrentColorChanged: {
            Light.color = currentColor
        }
    }
}
