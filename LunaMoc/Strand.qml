import QtQuick 2.0

Item {
    property var begin: DragHandle {
        id: begin
    }
    property var end: DragHandle {
        id: end
    }

    property alias model: repeater.model

    Item {
        Repeater {
            id: repeater
            model: provider.data
            delegate: Pixel {
                size: 100
                color: modelData.color
            }
            onItemAdded: {
                //for (var i = 0; i < count; ++i) {
                    var c = item
                    var t = index / (count - 1)
                    if (count < 2) t = 0.0
                    c.x = Qt.binding(getXBinder(t))
                    c.y = Qt.binding(getYBinder(t))
                //}
            }

            function lerp(a, b, t) {
                return a * (1 - t) + b * t
            }

            function getXBinder(t) {
                return function () {
                    return lerp(begin.x, end.x, t)
                }
            }

            function getYBinder(t) {
                return function () {
                    return lerp(begin.y, end.y, t)
                }
            }
        }
    }
}
