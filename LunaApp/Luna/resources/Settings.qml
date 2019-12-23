import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

Item {
    id: settingsItem

    ColumnLayout {
        id: columnLayout
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        transformOrigin: Item.Center

        GroupBox {
            id: whiteBalanceGroupBox
            width: 200
            height: 200
            title: qsTr("White Balance")
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            ColumnLayout {
                id: columnLayout1
                transformOrigin: Item.Center
                anchors.fill: parent

                Slider {
                    id: redWhiteBalanceslider
                    Layout.fillWidth: true
                    value: 0.5

                    Label {
                        id: label
                        text: qsTr("Red")
                    }
                }

                Slider {
                    id: greenWhiteBalanceslider
                    Layout.fillWidth: true
                    value: 0.5

                    Label {
                        id: label1
                        text: qsTr("Green")
                    }
                }

                Slider {
                    id: blueWhiteBalanceslider
                    Layout.fillWidth: true
                    value: 0.5

                    Label {
                        id: label2
                        text: qsTr("Blue")
                    }
                }
            }
        }

        GroupBox {
            id: gammaGroupBox
            width: 200
            height: 200
            Layout.fillWidth: true
            title: qsTr("Gamma")

            Slider {
                id: gammaSlider
                anchors.fill: parent
                value: 0.5
            }
        }
    }
}
