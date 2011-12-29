import Qt 4.7

Item {
    id: stopsListDelegate
    height: Math.round(menuBar.height * 0.8)
    width: stopsListView.width
    clip: true

    Rectangle {
        id: stopsDelegateContent
        width: parent.width
        height: parent.height - 1
        color: "#000000"

        Text {
            id: nameBox
            text: stopName
            color: "#FFFFFF"
            font.pointSize: 7
            font.bold: true

            anchors.leftMargin: 5
            anchors.verticalCenter: stopsDelegateContent.verticalCenter
        }

        Text {
            id: communeBox
            text: "(" + stopCommune + ")"
            color: "#FFFFFF"
            font.pointSize: 4

            anchors.left: nameBox.right
            anchors.leftMargin: 5
            anchors.verticalCenter: stopsDelegateContent.verticalCenter
        }

        MouseArea {
            id: stopsDelegateMA
            anchors.fill: stopsDelegateContent
            onClicked: stopsListView.indexChanged(stopName, stopID)
        }

        states: State {
                name: "changeColor"
                when:  stopsDelegateMA.pressed == true
                PropertyChanges {
                        target: stopsDelegateContent
                        color: "#ff8e00"
                }
        }
    }

    Rectangle {
        id: bottomLine
        height: 1
        width: parent.width
        color: "#FFFFFF"

        anchors.top: stopsDelegateContent.bottom
    }
}
