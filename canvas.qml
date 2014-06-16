import QtQuick 2.1
import ru.sibirix.osc 1.0

Rectangle {
    color: 'black'

    Image {
        source: 'image://canvas/main'
        opacity: .7
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
        }

        onPressed: {
            rect.width = 0
            rect.height = 0
            rect.x = mouseX
            rect.y = mouseY
            rect.visible = true
        }

        property bool xDirection
        property bool yDirection

        onPositionChanged: {
            if (mouseX < rect.x) {
                xDirection = true
            } else if (mouseX > rect.x + rect.width) {
                xDirection = false
            }

            if (mouseY < rect.y) {
                yDirection = true
            } else if (mouseY > rect.y + rect.height) {
                yDirection = false
            }

            if (xDirection) {
                rect.width += rect.x - mouseX
                rect.x = mouseX
            } else {
                rect.width = mouseX - rect.x
            }

            if (yDirection) {
                rect.height += rect.y - mouseY
                rect.y = mouseY
            } else {
                rect.height = mouseY - rect.y
            }
        }

        onReleased: {
            server.upload()
        }
    }

    Server {
        id: server
    }

    Rectangle {
        id: rect
        visible: false
        clip: true

        Image {
            id: image
            source: 'image://canvas/main'
            x: -rect.x
            y: -rect.y

        }
    }
}
