import QtQml 2.2
import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Item {
    id: lightItem
    property color color
    property real whiteness
    property bool colorFromTheme
    onColorChanged: {
        Light.color = color;
    }
    onWhitenessChanged: {
        Light.whiteness = whiteness;
    }
    onColorFromThemeChanged: {
        Light.colorFromTheme = colorFromTheme;
    }

    Component.onCompleted: {
        color = Light.color;
        whiteness = Light.whiteness;
        colorFromTheme = Light.colorFromTheme;
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
        anchors.fill: parent
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.topMargin: 20
        columns: 2

        CheckBox {
            id: colorFromThemeCheckBox
            Layout.fillWidth:  true
            checked: lightItem.colorFromTheme
            Label {
                text: qsTr("Get color from system theme")
            }
            onCheckedChanged: {
                if(lightItem.colorFromTheme !== checked){
                    lightItem.colorFromTheme = checked
                }
            }
        }

        Rectangle {
            id: colorButton
            height: 20
            Layout.fillWidth: true
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
                text: qsTr("Blue")
            }
            onPositionChanged: {
                if(lightItem.color.b !== position){
                    lightItem.color.b = position
                }
            }
        }

        Slider {
            id: whitenessSlider
            Layout.fillWidth: true
            value: lightItem.whiteness
            wheelEnabled: true
            Label {
                text: qsTr("White")
            }
            onPositionChanged: {
                if(lightItem.whiteness !== position){
                    lightItem.whiteness = position
                }
            }
        }
    }
}
