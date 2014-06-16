import QtQuick 2.1
import ru.sibirix.osc 1.0

Rectangle {
    Image {
        source: "image://canvas/main"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            server.upload("/home/ismd/Загрузки/tmp.png")
        }
    }

    Server {
        id: server
    }
}
