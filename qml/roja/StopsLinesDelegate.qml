import Qt 4.7

Item {
    id: stopsLinesListDelegate
    height: Math.round(menuBar.height * 0.7)
    width: stopsLinesListView.width
    clip: true

    Rectangle {
        id: stopsLinesDelegateContent
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
            anchors.verticalCenter: stopsLinesDelegateContent.verticalCenter
        }

        Text {
            id: wayBox
            text: lineWayName
            color: "#FFFFFF"
            font.pointSize: 6
            font.bold: true

            anchors.left: textBox.right
            anchors.leftMargin: 5
            anchors.verticalCenter: stopsLinesDelegateContent.verticalCenter
        }

        MouseArea {
            id: stopsLinesMA
            anchors.fill: parent
            onClicked: stopsLinesListView.indexChanged(lineNumber, lineWayName, lineRouteID)
        }

        states: State {
                name: "changeColor"
                when:  stopsLinesMA.pressed == true
                PropertyChanges {
                        target: stopsLinesDelegateContent
                        color: "#ff8e00"
                }
        }
    }

    Rectangle {
        id: bottomLine
        height: 1
        width: parent.width
        color: "#FFFFFF"

        anchors.top: stopsLinesDelegateContent.bottom
    }
}
