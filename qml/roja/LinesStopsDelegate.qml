import Qt 4.7

Item {
    id: linesStopsListDelegate
    height: Math.round(menuBar.height * 0.7)
    width: linesStopsListView.width
    clip: true

    Rectangle {
        id: linesStopsDelegateContent
        width: parent.width
        height: parent.height - 1
        color: "#000000"

        Text {
            id: nameBox
            text: stopName
            color: "#FFFFFF"
            font.pointSize: 7
            font.bold: true
            textFormat: Text.RichText

            anchors.leftMargin: 5
            anchors.verticalCenter: linesStopsDelegateContent.verticalCenter
        }

        Text {
            id: communeBox
            text: "(" + stopCommune + ")"
            color: "#FFFFFF"
            font.pointSize: 4

            anchors.left: nameBox.right
            anchors.leftMargin: 5
            anchors.verticalCenter: linesStopsDelegateContent.verticalCenter
        }

        MouseArea {
            id: linesStopsMA
            anchors.fill: parent
            onClicked: linesStopsListView.indexChanged(lineID, routeID, stopID, stopName, routesDetailsID)
        }

        states: State {
                name: "changeColor"
                when:  linesStopsMA.pressed == true
                PropertyChanges {
                        target: linesStopsDelegateContent
                        color: "#ff8e00"
                }
        }
    }

    Rectangle {
        id: bottomLine
        height: 1
        width: parent.width
        color: "#FFFFFF"

        anchors.top: linesStopsDelegateContent.bottom
    }
}
