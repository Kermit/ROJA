import Qt 4.7

Rectangle {
    property string text
    property int textPointSize : 7

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
        font.pointSize: textPointSize
        font.bold: true
        color: "#FFFFFF"
        anchors.centerIn: parent
        textFormat: Text.RichText
    }
}
