import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0


ApplicationWindow {
    id: window
    visible: true
    width: 640
    minimumWidth: 640
    height: 800
    minimumHeight: 800
    title: qsTr("Luna")


    header: ToolBar {
        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "qrc:/images/drawer.png"
                }
                onClicked: {
                    drawerDevices.open()
                }
            }

            Label {
                id: titleLabel
                text: listView.currentItem ? listView.currentItem.text : "Luna Client"
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "qrc:/images/menu.png"
                }
                onClicked: settingsPopup.open()
            }
        }
    }

    Drawer {
        id: drawerDevices
        width: Math.min(window.width, window.height) / 10 * 9
        height: window.height
        //dragMargin: stackView.depth > 1 ? 0 : undefined

        ListView {
            id: listView
            currentIndex: 0
            anchors.fill: parent

            delegate: ItemDelegate {
                width: parent.width
                text: model.title
                highlighted: ListView.isCurrentItem
                onClicked: {
                    if (listView.currentIndex != index) {
                        listView.currentIndex = index
                        //stackView.push(model.source)
                    }
                    drawerDevices.close()
                }
            }

            model: ListModel {
                ListElement { title: "TV" }//; source: "qrc:/pages/BusyIndicatorPage.qml" }
                ListElement { title: "Room" }//; source: "qrc:/pages/ButtonPage.qml" }
                ListElement { title: "Fridge" }//; source: "qrc:/pages/CheckBoxPage.qml" }
            }
        }
    }

    Popup {
        id: settingsPopup
        x: (window.width - width) / 2
        y: 0
        width: window.width * 0.9
        height: window.height * 0.9
        modal: true
        focus: true

        contentItem: ColumnLayout {
            id: columnLayout
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.rightMargin: 20
            anchors.leftMargin: 20
            transformOrigin: Item.Center
        }
    }

    SwipeView {
        anchors.fill: parent
        id: swipeView
        objectName: "swipeView"
        currentIndex: tabBar.currentIndex

        signal indexChanged(int index)

        onCurrentIndexChanged: indexChanged(currentIndex)
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        Repeater {
            model: TabNames
            TabButton {
                text: modelData
            }
        }
    }
}
