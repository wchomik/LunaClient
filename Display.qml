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
