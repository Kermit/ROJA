import Qt 4.7

Item {
    id: routesListDelegate
    height: Math.round(menuBar.height * 0.8)
    width: routeDetailsListView.width
    clip: true

    Rectangle {
        id: routesListDelegateContent
        width: parent.width
        height: parent.height - 1
        color: "#000000"

        Text {
            id: routeText
            text: route
            color: "#FFFFFF"
            font.pointSize: 7
            font.bold: true
            textFormat: Text.RichText

            anchors.leftMargin: 5
            anchors.verticalCenter: routesListDelegateContent.verticalCenter
        }

        MouseArea {
            id: routeDelegateMA
            anchors.fill: parent
            onClicked: routeDetailsListView.indexChanged(routedetailsID, routeIDs, route)
        }

        states: State {
                name: "changeColor"
                when:  routeDelegateMA.pressed == true
                PropertyChanges {
                        target: routesListDelegateContent
                        color: "#ff8e00"
                }
        }
    }

    Rectangle {
        id: bottomLine
        height: 1
        width: parent.width
        color: "#FFFFFF"

        anchors.top: routesListDelegateContent.bottom
    }
}
