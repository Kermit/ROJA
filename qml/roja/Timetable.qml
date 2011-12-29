import Qt 4.7

Rectangle {
    id: timetableSection
    anchors.fill: parent
    objectName: "timetableSection"
    color: "#FFFFFF"

    Rectangle {
        id: timetableContent
        width: parent.width
        height: parent.height
        color: "#000000"

        ListView {
            id: timetableListView
            objectName: "timetableListView"
            anchors.fill: parent
            model: timetableModel
            clip: true
            delegate: TimetableDelegate {}
        }
    }
}
