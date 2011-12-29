import Qt 4.7

Rectangle {
    property string page : "Main"

    id: stopsSection
    objectName: "stopsSection"
    width: content.width
    height: content.height
    color: "#000000"

    TitleBar {
        id: stopsTitleBar
        objectName: "stopsTitleBar"
        text: "Przystanki"

        BackButton {
            objectName: "stopsBackButton"
            page: stopsSection.page
        }

        Rectangle {
            signal searchButtonClicked()

            id: stopSearchButton
            objectName: "stopSearchButton"
            color: "red"
            height: parent.height - 10
            width: height
            visible: true
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 5
            anchors.right: parent.right

            MouseArea {
                id: backMA
                anchors.fill: parent
                onClicked: stopSearchButton.searchButtonClicked()
            }
        }
    }

    Search {
        id: stopsSearch
        objectName: "stopsSearch"
        anchors.top: stopsTitleBar.bottom
        visible: true
    }

    Rectangle {
        id: stopsContent
        objectName: "stopsContent"
        width: parent.width
        height: parent.height - stopsTitleBar.height - stopsSearch.height
        anchors.top: stopsSearch.bottom
        visible: true
        color: "#000000"

        ListView {
            signal indexChanged(string stopname, int stopid)

            id: stopsListView
            objectName: "stopsListView"
            anchors.fill: parent
            model: stopsModel
            clip: true
            delegate: StopsDelegate {}
            header:
                Rectangle {
                    height: 1
                    width: parent.width
                    color: "#FFFFFF"
                }
        }
    }

    Rectangle {
        id: stopsLinesContent
        objectName: "stopsLinesContent"
        width: parent.width
        height: parent.height - stopsTitleBar.height - stopsSearch.height
        anchors.top: stopsSearch.bottom
        color: "#000000"
        visible: false

        Loader {
            id: stopsLinesLoader
            anchors.fill: parent
            objectName: "stopsLinesLoader"
            source: ""
        }
    }
}
