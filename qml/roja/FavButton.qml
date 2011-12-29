import Qt 4.7

Rectangle {
    property string text
    property string backColor: "#303030"

    id: favButton
    width: parent.width
    height: buttonContent.height + buttonTitle.height
    state: "hide"
    color: backColor

    Rectangle {
        id: buttonTitle
        height: Math.round(favsContent.height * 0.12)
        color: backColor
        anchors.top: favButton.top

        Text {
            text: favButton.text
            font.bold: true
            font.pointSize: 7
            color: "#FFFFFF"

            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 5
        }
    }

    Rectangle {
        id: buttonContent
        width: parent.width
        height: 0
        color: "#000000"
        anchors.top: buttonTitle.bottom

        Rectangle {
            anchors.fill: parent            
            color: "#000000"

            ListView {
                id: favListView
                anchors.fill: parent
                delegate:
                    Text {
                    text: "Cos" + name + " - " + value
                    color: "#FFFFFF"
                }
            }
        }
    }

    states: [
        State {
            name: "show"
            PropertyChanges {
                target: buttonContent;
                height: Math.round(favsContent.height - (Math.round(favsContent.height * 0.12) * 3))
            }
        },
        State {
            name: "hide"
            PropertyChanges {
                target: buttonContent;
                height: 0
            }
        }
    ]
}
