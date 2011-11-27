import Qt 4.7

Rectangle {
    property string titleBarText

    id: favsPage
    width: favs.width
    height: favs.height
    color: "#000000"

    Rectangle {
        id: titleBar
        width: parent.width
        height: Math.round(parent.height * 0.1)

        Image {
            anchors.fill: parent
            source: "qrc:/images/titleBarBackground.png"
            fillMode: Image.Tile
        }

        Text {
            text: favsPage.titleBarText
            font.pointSize: 9
            font.bold: true
            color: "#FFFFFF"

            anchors.centerIn: parent
        }
    }

}
