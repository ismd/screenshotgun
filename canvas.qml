import QtQuick 2.2
import QtQuick.Controls 1.0
import ru.sibirix.osc 1.0

Rectangle {
    color: 'black'

    Image {
        source: 'image://canvas/main'
        opacity: .7
    }

    MouseArea {
        anchors.fill: parent
        property bool rectReady: false

        onClicked: {
            if (!rectReady) {
                return
            }

            canvas.update(mouseX - rect.x, mouseY - rect.y)
        }

        onPressed: {
            if (rectReady) {
                return
            }

            row.visible = false
            rect.width = 0
            rect.height = 0
            rect.x = mouseX
            rect.y = mouseY
            rect.visible = true
        }

        property bool xDirection
        property bool yDirection

        onPositionChanged: {
            if (rectReady) {
                return
            }

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
            if (rectReady) {
                return
            }

            rectReady = true
            row.x = rect.x
            row.y = rect.y + rect.height
            row.visible = true
        }
    }

    Row {
        id: row
        visible: false
        width: rect.width
        height: 50

        Button {
            id: lineButton
            width: 100
            height: parent.height
            text: 'Line'
        }

        Button {
            id: rectangleButton
            width: 100
            height: parent.height
            text: 'Rectangle'
        }

        Button {
            id: textButton
            width: 100
            height: parent.height
            text: 'Text'
        }

        Button {
            id: submit
            width: 100
            height: parent.height
            text: 'Submit'
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

        Canvas {
            id: canvas
            width: image.width
            height: image.height

            property int prevX
            property int prevY

            function update(x, y) {
                prevX = x
                prevY = y
                requestPaint()
            }

            onPaint: {
                var ctx = getContext('2d')

                ctx.lineWidth = 4
                ctx.strokeStyle = "blue"
                //ctx.fillStyle = "steelblue"

                ctx.beginPath()
                ctx.moveTo(50, 50)
                ctx.lineTo(prevX, prevY)
                ctx.closePath()

                //ctx.fill()
                ctx.stroke()
            }
        }
    }
}
