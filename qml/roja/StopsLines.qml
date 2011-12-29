import Qt 4.7

Rectangle {
    id: stopsLinesSection
    objectName: "stopsLinesSection"
    width: content.width
    height: content.height
    color: "#000000"

    Rectangle {
        id: stopsLinesContent
        objectName: "stopLinesBox"
        width: parent.width
        height: parent.height - stopsTitleBar.height
        visible: true
        color: "#000000"

        ListView {
            signal indexChanged(string linenumber, string linewayname, int routesdetailsid)

            id: stopsLinesListView
            objectName: "stopsLinesListView"
            anchors.fill: parent
            model: stopsLinesModel
            clip: true
            delegate: StopsLinesDelegate {}
            header:
                Rectangle {
                    height: 1
                    width: parent.width
                    color: "#FFFFFF"
                }
        }
    }

    Rectangle {
        id: slDetailsContent
        objectName: "slDetailsContent"
        width: parent.width
        height: parent.height - stopsTitleBar.height
        color: "#000000"
        visible: false

        ListView {
            id: timetableListView
            objectName: "timetableListView"
            anchors.fill: parent
            model: stopsTimetableModel
            clip: true
            delegate: TimetableDelegate {}
        }
    }
}
