import Qt 4.7

Image {
    property string page
    signal backClicked(string page)

    id: backButton
    source: "qrc:/images/backIcon.png"
    //color: "red"
    height: parent.height - 4
    width: height
    visible: false
    anchors.verticalCenter: parent.verticalCenter
    anchors.leftMargin: 5
    anchors.left: parent.left
    smooth: true
    fillMode: Image.PreserveAspectFit

    MouseArea {
        id: backMA
        anchors.fill: parent
        onClicked: backButton.backClicked(backButton.page)
    }   
}
