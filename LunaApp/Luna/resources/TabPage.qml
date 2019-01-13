import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQml 2.12

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

        Instantiator {
            model: root.model
            delegate: QtObject {
                property var obj: qml
            }

            onObjectAdded: {
                 swipeView.insertItem(index, object.obj)

            }
            onObjectRemoved: {
                swipeView.takeItem(index)
            }
        }
    }

    footer: TabBar {
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
