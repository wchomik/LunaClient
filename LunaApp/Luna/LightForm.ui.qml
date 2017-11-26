import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    id: item1
    width: 640
    height: 480

    GridLayout {
        id: gridLayout
        height: 100
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        columns: 2

        Button {
            id: colorButton
            text: qsTr("")
            Layout.fillHeight: true
            Layout.rowSpan: 4
        }

        Slider {
            id: redSlider
            Layout.fillWidth: true
            value: 0.5

            Label {
                id: label
                text: qsTr("Red")
            }
        }

        Slider {
            id: greenSlider
            Layout.fillWidth: true
            value: 0.5

            Label {
                id: label1
                text: qsTr("Green")
            }
        }

        Slider {
            id: blueSlider
            Layout.fillWidth: true
            value: 0.5

            Label {
                id: label2
                text: qsTr("Blue")
            }
        }

        Slider {
            id: brightnessSlider
            Layout.fillWidth: true
            value: 0.5

            Label {
                id: label3
                text: qsTr("Brightness")
            }
        }
    }
}
