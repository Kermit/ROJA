import QtQuick 1.0

Rectangle {
    signal filter(string text)
    property bool inputFocus : true

    id: search
    height: 0
    width: parent.width
    color: "#000000"

    states: [
        State {
            name: "show"
            PropertyChanges {
                target: search;
                height: Math.round(parent.height * 0.1)
            }
        },
        State {
            name: "hide"
            PropertyChanges {
                target: search;
                height: 0
            }
            PropertyChanges {
                target: input;
                focus: false
            }
        }
    ]

    Rectangle {
        id: inputBox
        width: Math.round(parent.width * 0.9)
        height: Math.round(parent.height * 0.9)
        anchors.centerIn: parent
        color: "#FFFFFF"

        MouseArea {
            anchors.fill: parent
            onDoubleClicked: input.selectAll()
        }

        TextInput {
            id: input
            width: parent.width - 10
            height: parent.height - 2
            font.pointSize: 11
            selectByMouse: true
            focus: search.inputFocus
            inputMethodHints: Qt.ImhNoPredictiveText
            onFocusChanged: {
                if (!input.focus) {
                    input.closeSoftwareInputPanel();
                    text = ""
                }                
            }

            anchors.centerIn: parent
            onTextChanged:  {
                search.filter(text)
            }

            onAccepted:
            {                
                input.closeSoftwareInputPanel();
                input.focus = false
            }

        }
    }
}
