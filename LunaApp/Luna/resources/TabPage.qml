import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

Page {
    id: root
    property var model
    signal tabSelected(int index)

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: bar.currentIndex
        interactive: false

        onCurrentIndexChanged: root.tabSelected(currentIndex)

        Repeater {
            model: root.model
            delegate: Item {
                id: container
                children: [qml]
                Component.onCompleted: {
                    qml.anchors.fill = container;
                    qml.anchors.margins = 15;
                }
            }
        }
    }

    header: TabBar {
        id: bar
        currentIndex: swipeView.currentIndex
        Repeater {
            model: root.model
            delegate: TabButton {
                text: name
            }
        }
    }

}
