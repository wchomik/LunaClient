import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import Qt.labs.settings 1.0

Item {
    Settings {
        id: settings
        category: "Flame"
        property real temperatureLow: 1600
        onTemperatureLowChanged: Flame.temperatureLow = temperatureLow

        property real temperatureHigh: 3000
        onTemperatureHighChanged: Flame.temperatureHigh = temperatureHigh

        property alias flickerRate: flickerRate.value
        onFlickerRateChanged: Flame.flickerRate = flickerRate.value

        property alias brightness: brightness.value
        onBrightnessChanged: Flame.brightness = brightness.value
    }

    GridLayout {
        anchors.margins: 20
        anchors.fill: parent
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
            to: 1.0
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
            id: spacer
            Layout.fillHeight: true
        }
    }
}
