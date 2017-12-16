import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

GridLayout {
    id: root
    columns: 2

    Settings {
        id: settings
        category: "Light"
        property alias colorManual: root.color
        property alias whiteness: whitenessSlider.value
    }

    property color color: "white"
    onColorChanged: {
        Light.color = color
    }

    Label {
        text: qsTr("Red")
    }

    Slider {
        id: redSlider
        Layout.fillWidth: true
        value: root.color.r
        wheelEnabled: true
        onValueChanged: {
            root.color.r = value
        }
    }

    Label {
        text: qsTr("Green")
    }

    Slider {
        id: greenSlider
        Layout.fillWidth: true
        value: root.color.g
        wheelEnabled: true
        onValueChanged: {
            root.color.g = value
        }
    }

    Label {
        text: qsTr("Blue")
    }

    Slider {
        id: blueSlider
        Layout.fillWidth: true
        value: root.color.b
        wheelEnabled: true
        onValueChanged: {
            root.color.b = value
        }
    }

    Label {
        text: qsTr("White")
    }

    Slider {
        id: whitenessSlider
        Layout.fillWidth: true
        value: Light.whiteness
        wheelEnabled: true
        onPositionChanged: {
            Light.whiteness = value
        }
    }
}
