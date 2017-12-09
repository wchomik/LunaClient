import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Item {
    GridLayout {
        anchors.margins: 20
        anchors.fill: parent
        columns: 2
        Label {
            text: "Temperture"
        }

        RangeSlider {
            Layout.fillWidth: true
            from: 1000.0
            to: 10000.0
            first {
                value: Flame.temperatureLow
                onValueChanged: Flame.temperatureLow = first.value
            }
            second {
                value: Flame.temperatureHigh
                onValueChanged: Flame.temperatureHigh = second.value
            }
        }

        Label {
            text: "Brightness"
        }

        Slider {
            Layout.fillWidth: true
            from: 0.0
            to: 10.0
            value: Flame.brightness
            onValueChanged: Flame.brightness = value
        }

        Label {
            text: "Flicker"
        }

        Slider {
            Layout.fillWidth: true
            from: 0.0
            to: 1.0
            value: Flame.flickerRate
            onValueChanged: Flame.flickerRate = value
        }

        Item {
            id: spacer
            Layout.fillHeight: true
        }
    }
}
