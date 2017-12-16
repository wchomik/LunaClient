import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import Qt.labs.settings 1.0

Item {
    Settings {
        category: "Light"
        property alias brightness: brightnessSlider.value
        property alias source: comboBox.currentIndex
    }

    GridLayout {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 20
        columns: 2

        Label {
            text: qsTr("Brightness")
        }

        Slider {
            id: brightnessSlider
            Layout.fillWidth: true
            from: 0
            to: 1
            value: 1
            onValueChanged: {
                Light.brightness = value
            }
        }

        ComboBox {
            id: comboBox
            Layout.fillWidth: true
            Layout.columnSpan: 2
            model: ListModel {
                ListElement {
                    name: QT_TR_NOOP("Color from system theme")
                    qml: "qrc:/LightPlugin/ColorFromThemeControl.qml"
                    source: 3
                }
                ListElement {
                    name: QT_TR_NOOP("Color picker")
                    qml: "qrc:/LightPlugin/ColorPickerControl.qml"
                    source: 0
                }
                ListElement {
                    name: QT_TR_NOOP("Temperature")
                    qml: "qrc:/LightPlugin/TemperatureControl.qml"
                    source: 1
                }
                ListElement {
                    name: QT_TR_NOOP("Manual control")
                    qml: "qrc:/LightPlugin/ManualControl.qml"
                    source: 2
                }
            }
            textRole: "name"
            displayText: qsTr(currentText)
            onCurrentIndexChanged: {
                var currentItem = model.get(currentIndex)
                loader.source = currentItem.qml
                Light.source = currentItem.source
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
            Layout.fillWidth: true
            Layout.columnSpan: 2
        }
    }
}
