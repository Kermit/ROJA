import Qt 4.7

Rectangle {
    property string page : "Main"

    id: linesSection
    objectName: "linesSection"
    width: content.width
    height: content.height
    color: "#000000"

    TitleBar {        
        id: linesTitleBar
        objectName: "linesTitleBar"
        text: "Linie"

        BackButton {
            objectName: "linesBackButton"
            page: linesSection.page
        }

        Image {
            signal searchButtonClicked()

            id: searchButton
            objectName: "searchButton"
            source: "qrc:/images/lupaIcon.png"
            smooth: true
            height: parent.height - 4
            width: height
            visible: true
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 5
            anchors.right: parent.right

            MouseArea {
                id: backMA
                anchors.fill: parent
                onClicked: searchButton.searchButtonClicked()
            }
        }
    }

    Search {
        id: linesSearch
        objectName: "linesSearch"
        anchors.top: linesTitleBar.bottom
        visible: true                
    }

    Rectangle {
        id: linesContent
        objectName: "linesContent"
        width: parent.width
        height: parent.height - linesTitleBar.height - linesSearch.height
        anchors.top: linesSearch.bottom
        visible: true
        color: "#000000"

        ListView {
            signal indexChanged(int lineid, int routeid, string linename, string linewayname)

            id: linesListView
            objectName: "linesListView"
            anchors.fill: parent
            model: linesModel
            clip: true
            delegate: LinesDelegate {}
            header:
                Rectangle {
                    height: 1
                    width: parent.width
                    color: "#FFFFFF"
                }
        }
    }

    Rectangle {
        id: linesStopsContent
        objectName: "linesStopsBox"
        width: parent.width
        height: parent.height - linesTitleBar.height - linesSearch.height
        anchors.top: linesSearch.bottom
        color: "#000000"
        visible: false

        Loader {
            id: linesStopsLoader
            anchors.fill: parent
            objectName: "linesStopsLoader"
            source: ""
        }
    }
}
