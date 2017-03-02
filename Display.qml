import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    id: displayItem
    width: window.width
    /*anchors.right: parent.right
    anchors.left: parent.left
    anchors.top: parent.top*/

    RowLayout{
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.topMargin: 20

        GroupBox {
            GridLayout {
                id: gridLayout
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top

                columns: 2

                Pane{

                }

                RangeSlider {
                    id: horizontalRangeSlider
                    wheelEnabled: true
                    first.value: Luna.screen.left
                    second.value: Luna.screen.right

                    first.onPositionChanged: {
                        Luna.screen.left = first.position;
                    }
                    second.onPositionChanged: {
                        Luna.screen.right = second.position;
                    }
                }

                RangeSlider {
                    id: verticalRangeSlider
                    orientation: "Vertical"
                    Layout.fillHeight: true
                    wheelEnabled: true
                    first.value: Luna.screen.bottom
                    second.value: Luna.screen.top

                    first.onPositionChanged: {
                        Luna.screen.bottom = first.position;
                    }
                    second.onPositionChanged: {
                        Luna.screen.top = second.position;
                    }
                }

                Rectangle {
                    id: colorButton
                    height: 200
                    width: 200
                    color: "white"
                }
            }
        }

        GroupBox {
            Layout.fillHeight: true
            ColumnLayout {
                SpinBox {
                    editable: true
                    value: Luna.screen.depth
                    from: 1
                    to: 30
                    stepSize: 1
                    Label {
                        id: depthLabel
                        font.pixelSize: 12
                        text: qsTr("Depth")
                    }
                    onValueChanged: {
                        Luna.screen.depth = value
                    }
                }

                SpinBox {
                    id: spinSharpnessRadius
                    editable: true
                    value: 0
                    Label {
                        id: sharpLabel
                        font.pixelSize: 12
                        text: qsTr("Sharpeness radius")
                    }
                }

                SpinBox {
                    id: spinSharpnessStep
                    editable: true
                    from: 0
                    value: 110
                    to: 100 * 100
                    stepSize: 100

                    property int decimals: 2
                    property real realValue: value / 100

                    validator: DoubleValidator {
                        bottom: Math.min(spinSharpnessStep.from, spinSharpnessStep.to)
                        top:  Math.max(spinSharpnessStep.from, spinSharpnessStep.to)
                    }

                    textFromValue: function(value, locale) {
                        return Number(value / 100).toLocaleString(locale, 'f', spinSharpnessStep.decimals)
                    }

                    valueFromText: function(text, locale) {
                        return Number.fromLocaleString(locale, text) * 100
                    }

                    Label {
                        id: stepLabel
                        font.pixelSize: 12
                        text: qsTr("Sharpeness steps")
                    }
                }
            }
        }
    }
}
