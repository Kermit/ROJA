import Qt 4.7

Rectangle {
    property string text
    property int textPointSize : 7

    id: titleBar
    width: parent.width
    height: Math.round(parent.height * 0.12)

    Image {
        anchors.fill: parent
        source: "qrc:/images/titleBarBackground.png"
        fillMode: Image.Tile
    }

    Item {
        id: textBox

        width: (parent.width - 2*parent.height) - 10
        height: parent.height
        anchors.centerIn: parent

        Text {
            id: titleBarText

            text: titleBar.text
            font.pointSize: textPointSize
            font.bold: true
            color: "#FFFFFF"
            textFormat: Text.RichText
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            anchors.centerIn: parent
        }
    }
}
