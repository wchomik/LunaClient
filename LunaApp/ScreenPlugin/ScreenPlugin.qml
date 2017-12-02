import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    ColumnLayout {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.topMargin: 20

        GridLayout {
            Layout.fillWidth: true
            columns: 2

            Label {
                id: depthLabel
                text: qsTr("Depth")
            }

            SpinBox {
                editable: true
                value: Screen.depth
                from: 1
                to: 30
                stepSize: 1
                onValueChanged: {
                    Screen.depth = value
                }
            }

            Label {
                text: qsTr("Brightness")
            }

            Slider {
                Layout.fillWidth: true
                value: Screen.brightness
                wheelEnabled: true
                onValueChanged: {
                    Screen.brightness = position;
                }
            }

            Label {
                text: qsTr("Gamma")
            }

            Slider {
                Layout.fillWidth: true
                value: Screen.gamma
                wheelEnabled: true
                onValueChanged: {
                    Screen.gamma = value;
                }
            }

            Label {
                text: qsTr("Black level")
            }

            Slider {
                Layout.fillWidth: true
                from: 0.0
                to: 0.01
                value: Screen.blackLevel
                wheelEnabled: true
                onValueChanged: {
                    Screen.blackLevel = value;
                }
            }
        }
    }
}

