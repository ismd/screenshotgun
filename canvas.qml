import QtQuick 2.0

Rectangle {
    Image {
        source: "image://canvas/main"
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            object.save()
            object.upload()
            Qt.quit()
        }
    }
}
