import Qt 4.7

Item {
    id: timetableDelegate
    height: dayNameBox.paintedHeight + timetableBox.paintedHeight + timetableLegendBox.paintedHeight
    width: timetableListView.width
    clip: true

    Rectangle {
        id: timetableDelegateContent
        width: parent.width
        height: parent.height
        color: "#000000"

        Text {
            id: dayNameBox
            text: dayName
            color: "#FFFFFF"
            font.pointSize: 10
            font.bold: true
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere

            anchors.top: timetableDelegateContent.top
        }

        Text {
            id: timetableBox
            text: timetable
            color: "#FFFFFF"
            font.pointSize: 9
            width: parent.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            textFormat: Text.RichText

            anchors.top: dayNameBox.bottom
        }

        Text {
            id: timetableLegendBox
            text: timetableLegend
            color: "#FFFFFF"
            font.pointSize: 6
            width: parent.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere

            anchors.top: timetableBox.bottom
        }
    }
}
