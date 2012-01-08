import Qt 4.7

Rectangle {
    width: 360
    height: 360
    color: "#000000"

//    Rectangle {
//        id: mainBox
//        objectName: "mainBox"
//        width: 320
//        height: 455

        Rectangle {
            id: content
            width: parent.width
            height: parent.height - menuBar.height

//            Loader {
//                id: favsLoader
//                objectName: "favsLoader"
//                source: ""
//                visible: true
//            }

            Loader {
                id: linesLoader
                objectName: "linesLoader"
                source: ""
                visible: false
            }

            Loader {
                id: stopsLoader
                objectName: "stopsLoader"
                source: ""
                visible: false
            }

            Loader {
                id: routesLoader
                objectName: "routesLoader"
                source: ""
                visible: false
            }

            Loader {
                id: settingsLoader
                objectName: "settingsLoader"
                source: ""
                visible: false
            }
        }

        Rectangle {
            property int buttonW: Math.round(parent.width / 4);

            id: menuBar
            width: parent.width
            height: Math.round(parent.height * 0.15)
            y: parent.height - height

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#000000" }
                GradientStop { position: 0.49; color: "#222222" }
                GradientStop { position: 1.0; color: "#000000" }
            }

//            Button {
//                id: favButton
//                objectName: "favsButton"
//                buttonWidth: parent.buttonW
//                text: "Ulubione"
//                state: 'enable'

//                anchors.left: parent.left
//            }

            Button {
                id: linesButton
                objectName: "linesButton"
                buttonWidth: parent.buttonW
                text: "Linie"
                state: 'enable'

                anchors.left: parent.left
            }

            Button {
                id: stopsButton
                objectName: "stopsButton"
                buttonWidth: parent.buttonW
                text: "Przystanki"
                state: 'disable'

                anchors.left: linesButton.right
            }

            Button {
                id: routesButton
                objectName: "routesButton"
                buttonWidth: parent.buttonW
                text: "Trasy"
                state: 'disable'

                anchors.left: stopsButton.right
            }

            Button {
                id: exitButton
                objectName: "exitButton"
                buttonWidth: parent.buttonW
                text: "Zakończ"
                state: 'disable'

                anchors.left: routesButton.right
            }
        }
//    }
}
