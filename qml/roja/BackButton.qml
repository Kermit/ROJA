import Qt 4.7

Rectangle {
    property string page
    signal backClicked(string page)

    id: backButton
    color: "red"
    height: parent.height - 10
    width: height
    visible: false
    anchors.verticalCenter: parent.verticalCenter
    anchors.leftMargin: 5
    anchors.left: parent.left

    MouseArea {
        id: backMA
        anchors.fill: parent
        onClicked: backButton.backClicked(backButton.page)
    }
}
