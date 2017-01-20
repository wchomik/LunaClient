import QtQml 2.2
import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.1

Item {
    id: lightItem
    width: window.width
    /*anchors.right: parent.right
    anchors.left: parent.left
    anchors.top: parent.top*/

    //! [colordialog]
    ColorDialog {
        id: colorDialog
        //visible: colorDialogVisible.checked
        //modality: colorDialogModal.checked ? Qt.WindowModal : Qt.NonModal
        title: "Choose a color"
        color: "white"
        //showAlphaChannel: colorDialogAlpha.checked
        /*onAccepted: {
            redSlider.value = color.r
            greenSlider.value = color.g
            blueSlider.value = color.b
        }*/
    }
    //! [colordialog]

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
            color: Qt.rgba(redSlider.position, greenSlider.position, blueSlider.position)//colorDialog.color
            MouseArea {
                anchors.fill: parent
                onClicked: colorDialog.open()
            }
        }

        Slider {
            id: redSlider
            Layout.fillWidth: true
            value: colorDialog.color.r
            wheelEnabled: true
            Label {
                id: label
                text: qsTr("Red")
            }
        }

        Slider {
            id: greenSlider
            Layout.fillWidth: true
            value: colorDialog.color.g
            wheelEnabled: true
            Label {
                id: label1
                text: qsTr("Green")
            }
        }

        Slider {
            id: blueSlider
            Layout.fillWidth: true
            value: colorDialog.color.b
            wheelEnabled: true
            Label {
                id: label2
                text: qsTr("Blue")
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
