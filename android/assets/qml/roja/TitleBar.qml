import Qt 4.7

Rectangle {
    property string text

    id: titleBar
    width: parent.width
    height: Math.round(parent.height * 0.1)

    Image {
        anchors.fill: parent
        source: "qrc:/images/titleBarBackground.png"
        fillMode: Image.Tile
    }

    Text {
        id: titleBarText
        text: parent.text
        font.pointSize: 7
        font.bold: true
        color: "#FFFFFF"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
