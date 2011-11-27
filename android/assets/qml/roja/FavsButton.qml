import Qt 4.7

Rectangle {
    property string text

    height: favsTopBar.height
    width: Math.round(favsTopBar.width * 0.33)
    color: favsTopBar.color

    Text {
        text: parent.text
        anchors.fill: parent
        font.pointSize: 6
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
        anchors.fill: parent
        onClicked: parent.color = "#555555"
    }
}
