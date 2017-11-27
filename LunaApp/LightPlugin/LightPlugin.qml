import QtQml 2.2
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Item {
    ColorDialog {
        id: colorDialog
        title: "Choose a color"
        width: 450
        height: 450
        color: Light.color
        onCurrentColorChanged: {
            Light.color = currentColor
        }
    }

    GroupBox {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.topMargin: 20

        label: CheckBox {
            id: themeColorCheckBox
            checked: Light.themeColor
            onCheckedChanged: {
                Light.themeColor = checked
            }
            text: qsTr("Get color from system theme")
        }

        GridLayout {
            enabled: !themeColorCheckBox.checked
            anchors.fill: parent
            columns: 2

            Button {
                text: qsTr("Pick color")
                onClicked: colorDialog.open()
            }

            Rectangle {
                id: colorButton
                height: 40
                Layout.fillWidth: true
                color: Light.color
                radius: 8
            }

            Label {
                text: qsTr("Red")
            }

            Slider {
                id: redSlider
                Layout.fillWidth: true
                value: Light.color.r
                wheelEnabled: true
                onValueChanged: {
                    if (Light.color.r === value) return;
                    Light.color.r = value
                }
            }

            Label {
                text: qsTr("Green")
            }

            Slider {
                id: greenSlider
                Layout.fillWidth: true
                value: Light.color.g
                wheelEnabled: true
                onValueChanged: {
                    if (Light.color.g === value) return;
                    Light.color.g = value
                }
            }

            Label {
                text: qsTr("Blue")
            }

            Slider {
                id: blueSlider
                Layout.fillWidth: true
                value: Light.color.b
                wheelEnabled: true
                onValueChanged: {
                    if (Light.color.b === value) return;
                    Light.color.b = value
                }
            }

            Label {
                text: qsTr("White")
            }

            Slider {
                id: whitenessSlider
                Layout.fillWidth: true
                value: Light.whiteness
                wheelEnabled: true
                onPositionChanged: {
                    if (Light.whiteness === value) return;
                    Light.whiteness = value
                }
            }
        }

    }
}
