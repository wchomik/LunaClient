import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import Qt.labs.settings 1.0

ColumnLayout {
    spacing: 20

    GridLayout {
        columns: 2
        Label {
            text: qsTr("Brightness")
        }

        Slider {
            id: brightnessSlider
            Layout.fillWidth: true
            from: 0
            to: 1
            value: Model.brightness
            onValueChanged: {
                Model.brightness = value
            }
        }


        Label {
            text: qsTr("Whiteness")
        }

        Slider {
            id: whitenessSlider
            Layout.fillWidth: true
            from: 0
            to: 1
            value: Model.whiteness
            onValueChanged: {
                Model.whiteness = value;
            }
        }
    }

    ListModel {
        id: modes
        ListElement {
           name: QT_TR_NOOP("Color picker")
           qml: "ColorPickerControl.qml"
           source: 0
        }
        ListElement {
           name: QT_TR_NOOP("Temperature")
           qml: "TemperatureControl.qml"
           source: 1
        }
        ListElement {
           name: QT_TR_NOOP("Color from system theme")
           qml: "ColorFromThemeControl.qml"
           source: 2
        }
    }

    ComboBox {
        id: comboBox
        Layout.fillWidth: true
        model: modes
        textRole: "name"
        displayText: qsTr(currentText)
        currentIndex: Model.source
        onCurrentIndexChanged: {
            Model.source = model.get(currentIndex).source
        }
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.NoButton
            onWheel: {
                if (wheel.angleDelta.y < 0) {
                    comboBox.incrementCurrentIndex()
                } else {
                    comboBox.decrementCurrentIndex()
                }
                wheel.accepted = true
            }
        }
    }

    Loader {
        id: loader
        source: modes.get(comboBox.currentIndex).qml
        Layout.fillWidth: true
        Layout.fillHeight: true
    }
}
