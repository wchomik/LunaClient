import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import Qt.labs.settings 1.0

ColumnLayout {
    Settings {
        property alias smoothness: smoothnessSlider.value
    }

    GridLayout {
        Layout.fillWidth: true
        columns: 2

        Label {
            id: depthLabel
            text: qsTr("Depth")
        }

        SpinBox {
            editable: true
            value: Model.depth
            from: 1
            to: 50
            stepSize: 1
            onValueChanged: {
                Model.depth = value
            }
        }

        Label {
            text: qsTr("Brightness")
        }

        Slider {
            Layout.fillWidth: true
            value: Model.brightness
            wheelEnabled: true
            onValueChanged: {
                Model.brightness = position;
            }
        }

        Label {
            text: qsTr("Gamma")
        }

        Slider {
            Layout.fillWidth: true
            value: Model.gamma
            wheelEnabled: true
            onValueChanged: {
                Model.gamma = value;
            }
        }

        Label {
            text: qsTr("Black level")
        }

        Slider {
            Layout.fillWidth: true
            from: 0.0
            to: 0.01
            value: Model.blackLevel
            wheelEnabled: true
            onValueChanged: {
                Model.blackLevel = value;
            }
        }

        Label {
            text: qsTr("Smoothness")
        }

        Slider {
            id: smoothnessSlider
            Layout.fillWidth: true
            from: 0.0
            to: 1.0
            value: Model.smoothness
            wheelEnabled: true
            onValueChanged: {
                Model.smoothness = value;
            }
        }
    }

    Item {
        Layout.fillHeight: true
    }
}
