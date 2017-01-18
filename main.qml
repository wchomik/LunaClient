import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Luna")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Settings {
        }

        Light {
        }

        Display {
        }

        /*Page {
            Label {
                text: qsTr("Light")
                anchors.centerIn: parent
            }
        }*/
    }

    header: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Settings")
        }
        TabButton {
            text: qsTr("Light")
        }
        TabButton {
            text: qsTr("Display")
        }
    }
}
