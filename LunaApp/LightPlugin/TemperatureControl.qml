import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

RowLayout {
    Settings {
        category: "Light"
        property alias temperature: temperatureSlider.value
    }

    Label {
        text: qsTr("Color temperature")
    }

    Slider {
        id: temperatureSlider
        Layout.fillWidth: true
        from: 1666
        to: 12000
        value: 5500
        onValueChanged: {
            Light.temperature = value
        }
    }
}

