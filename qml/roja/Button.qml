import Qt 4.7

Rectangle {
    signal clicked();

    property string text
    property int buttonWidth

    property string color1: "#000000"
    property string color2: "#222222"

    id: button
    width: buttonWidth
    height: parent.height

    gradient: Gradient {
        GradientStop { position: 0.0; color: color1 }
        GradientStop { position: 0.49; color: color2 }
        GradientStop { position: 1.0; color: color1 }
    }

    Text {
        text: button.text
        font.bold: true
        font.pointSize: 5
        color: "#FFFFFF"

        anchors.verticalCenter: parent.verticalCenter
        //anchors.left: parent.left
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.leftMargin: 5
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            if (button.state == 'disable')
            button.clicked();
        }
    }

    states: [
        State {
            name: "enable"
            PropertyChanges {
                target: button;
                color1: "#111111"
                color2: "#333333"
            }
        },
        State {
            name: "disable"
            PropertyChanges {
                target: button;
                color1: "#000000"
                color2: "#222222"
            }
        }
    ]
}
