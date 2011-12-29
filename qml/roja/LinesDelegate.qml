import Qt 4.7

Item {
    id: listDelegate
    height: Math.round(menuBar.height * 0.8)
    width: linesListView.width
    clip: true

    Rectangle {
        id: linesDelegateContent
        width: parent.width
        height: parent.height - 1
        color: "#000000"

        Text {
            id: textBox
            text: lineNumber
            color: "#FFFFFF"
            font.pointSize: 12
            font.bold: true

            anchors.leftMargin: 5
            anchors.verticalCenter: linesDelegateContent.verticalCenter
        }

        Text {
            id: wayBox
            text: lineWayName
            color: "#FFFFFF"
            font.pointSize: 6
            font.bold: true

            anchors.left: textBox.right
            anchors.leftMargin: 5
            anchors.verticalCenter: linesDelegateContent.verticalCenter
        }

        MouseArea {
            id: linesDelegateMA
            anchors.fill: linesDelegateContent
            onClicked: linesListView.indexChanged(lineID, lineRouteID, lineNumber, lineWayName)
        }

        states: State {
                name: "changeColor"
                when:  linesDelegateMA.pressed == true
                PropertyChanges {
                        target: linesDelegateContent
                        color: "#ff8e00"
                }
        }
    }    

    Rectangle {
        id: bottomLine
        height: 1
        width: parent.width
        color: "#FFFFFF"

        anchors.top: linesDelegateContent.bottom
    }
}
