import QtQml 2.2
import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Item {
    id: lightItem
    width: window.width
    property color color
    onColorChanged: {
        //Luna.
    }

    ColorDialog {
        id: colorDialog
        title: "Choose a color"
        width: 400
        height: 400
        color: lightItem.color
        onCurrentColorChanged: {
            lightItem.color = currentColor
        }
    }

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

        Rectangle {
            id: colorButton
            width: 100
            Layout.fillHeight: true
            Layout.rowSpan: 3
            color: lightItem.color
            MouseArea {
                anchors.fill: parent
                onClicked: colorDialog.open()
            }
        }

        Slider {
            id: redSlider
            Layout.fillWidth: true
            value: lightItem.color.r
            wheelEnabled: true
            Label {
                id: label
                text: qsTr("Red")
            }
            onPositionChanged: {
                if(lightItem.color.r !== position){
                    lightItem.color.r = position
                }
            }
        }

        Slider {
            id: greenSlider
            Layout.fillWidth: true
            value: lightItem.color.g
            wheelEnabled: true
            Label {
                id: label1
                text: qsTr("Green")
            }
            onPositionChanged: {
                if(lightItem.color.g !== position){
                    lightItem.color.g = position
                }
            }
        }

        Slider {
            id: blueSlider
            Layout.fillWidth: true
            value: lightItem.color.b
            wheelEnabled: true
            Label {
                id: label2
                text: qsTr("Blue")
            }
            onPositionChanged: {
                if(lightItem.color.b !== position){
                    lightItem.color.b = position
                }
            }
        }

        /*Slider {
            id: brightnessSlider
            Layout.fillWidth: true
            value: 0.5

            Label {
                id: label3
                text: qsTr("Brightness")
            }
        }*/
    }
}
