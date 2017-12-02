import QtQuick 2.2
import QtQuick.Controls 2.2

Page {
    id: root
    property var tabs
    signal tabSelected(int index)
    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: bar.currentIndex

        onCurrentIndexChanged: root.tabSelected(currentIndex)

        contentChildren: root.tabs.items
    }

    footer: TabBar {
        id: bar
        currentIndex: swipeView.currentIndex
        Repeater {
            model: root.tabs.names
            TabButton {
                text: modelData
            }
        }
    }
}
