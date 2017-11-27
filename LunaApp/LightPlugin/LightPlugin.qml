import QtQml 2.2
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Item {
    id: lightItem

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

    ColumnLayout {
        id: gridLayout
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.topMargin: 20

        RowLayout {
            Label {
                text: qsTr("Get color from system theme")
            }
            CheckBox {
                id: themeColorCheckBox
                checked: Light.themeColor
                onCheckedChanged: {
                    Light.themeColor = checked
                }
            }
        }

        RowLayout {
            Button {
                text: qsTr("Pick color")
                onClicked: colorDialog.open()
            }
            Rectangle {
                id: colorButton
                height: 40
                Layout.fillWidth: true
                color: Light.color
            }
        }

        ColumnLayout {
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
        }

        ColumnLayout {
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
        }

        ColumnLayout {
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
        }

        ColumnLayout {
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
