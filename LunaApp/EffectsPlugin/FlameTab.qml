import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import Qt.labs.settings 1.0

GridLayout {
    Settings {
        id: settings
        category: "Flame"
        property real temperatureLow: 1600
        onTemperatureLowChanged: Model.temperatureLow = temperatureLow

        property real temperatureHigh: 3000
        onTemperatureHighChanged: Model.temperatureHigh = temperatureHigh

        property alias flickerRate: flickerRate.value
        onFlickerRateChanged: Model.flickerRate = flickerRate.value

        property alias brightness: brightness.value
        onBrightnessChanged: Model.brightness = brightness.value
    }

    columns: 2

    Label {
        text: qsTr("Temperture")
    }

    RangeSlider {
        id: temperature
        Layout.fillWidth: true
        from: 1000.0
        to: 10000.0
        first {
            value: settings.temperatureLow
            onValueChanged: {
                if (settings.temperatureLow !== first.value) {
                    settings.temperatureLow = first.value
                }
            }
        }
        second {
            value: settings.temperatureHigh
            onValueChanged: {
                if (settings.temperatureHigh !== second.value) {
                    settings.temperatureHigh = second.value
                }
            }
        }
    }

    Label {
        text: qsTr("Brightness")
    }

    Slider {
        id: brightness
        Layout.fillWidth: true
        from: 0.0
        to: 2.0
        value: 1.0
    }

    Label {
        text: qsTr("Flicker")
    }

    Slider {
        id: flickerRate
        Layout.fillWidth: true
        from: 0.0
        to: 1.0
        value: 0.33
    }

    Item {
        Layout.fillHeight: true
    }
}
