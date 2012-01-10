import Qt 4.7

Item {
    id: chooseStopListDelegate
    height: Math.round(menuBar.height * 0.8)
    width: chooseStopList.width
    clip: true

    Rectangle {
        id: chooseStopListDelegateContent
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
            anchors.verticalCenter: chooseStopListDelegateContent.verticalCenter
        }

        Text {
            id: communeBox
            text: "(" + stopCommune + ")"
            color: "#FFFFFF"
            font.pointSize: 4

            anchors.left: nameBox.right
            anchors.leftMargin: 5
            anchors.verticalCenter: chooseStopListDelegateContent.verticalCenter
        }

        MouseArea {
            id: stopsDelegateMA
            anchors.fill: parent
            onClicked: {
                chooseStopList.indexChanged(stopName, stopID);
                chooseStopSearch.state = 'hide';                
            }
        }

        states: State {
                name: "changeColor"
                when:  stopsDelegateMA.pressed == true
                PropertyChanges {
                        target: chooseStopListDelegateContent
                        color: "#ff8e00"
                }
        }
    }

    Rectangle {
        id: bottomLine
        height: 1
        width: parent.width
        color: "#FFFFFF"

        anchors.top: chooseStopListDelegateContent.bottom
    }
}
