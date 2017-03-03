import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    id: displayItem
    width: window.width

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

                Slider {
                    value: Luna.screen.brightness
                    onPositionChanged: {
                        Luna.screen.brightness = position;
                    }

                    Label {
                        text: qsTr("Brightness")
                    }
                }

                Slider {
                    value: Luna.screen.gamma
                    onPositionChanged: {
                        Luna.screen.gamma = position;
                    }

                    Label {
                        text: qsTr("Gamma")
                    }
                }
            }
        }
    }
}
