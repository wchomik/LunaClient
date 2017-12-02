import QtQuick 2.2
import QtQuick.Controls 2.2

Page {
    property alias name: swipeView.objectName
    property alias model: tabBar.model
    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: bar.currentIndex

        signal indexChanged(int index)

        onCurrentIndexChanged: indexChanged(currentIndex)
    }

    footer: TabBar {
        id: bar
        currentIndex: swipeView.currentIndex
        Repeater {
            id: tabBar
            TabButton {
                text: modelData
            }
        }
    }
}
