import Qt 4.7

Rectangle {
    id: linesStopsSection
    objectName: "linesStopsSection"
    width: content.width
    height: content.height
    color: "#000000"

    Rectangle {
        id: linesStopsContent
        objectName: "linesStopsContentS"
        width: parent.width
        height: parent.height - linesTitleBar.height
        visible: true
        color: "#000000"

        ListView {
            signal indexChanged(int lineid, int routeid, int stopid, string stopname, int routesdetailsid)

            id: linesStopsListView
            objectName: "linesStopsListView"
            anchors.fill: parent
            model: linesStopsModel
            clip: true
            delegate: LinesStopsDelegate {}
            header:
                Rectangle {
                    height: 1
                    width: parent.width
                    color: "#FFFFFF"
                }
        }
    }

    Rectangle {
        id: linesDetailsContent
        objectName: "linesDetailsContent"
        width: parent.width
        height: parent.height - linesTitleBar.height
        color: "#000000"
        visible: false

        ListView {
            id: timetableListView
            objectName: "timetableListView"
            anchors.fill: parent
            model: linesTimetableModel
            clip: true
            delegate: TimetableDelegate {}
        }
    }
}
