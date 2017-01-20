import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles.Flat 1.0
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.3
import QtQuick.LocalStorage 2.0

Item {
    width: 400
    height: 400

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        Rectangle {
            id: rectangle1
            width: 200
            height: 200
            color: "#ffffff"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
        }

        Pane {
            id: pane
            width: 200
            height: 200
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

            Rectangle {
                id: rectangle
                width: 200
                height: 200
                color: "#ffffff"
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            }
        }

    }
}
