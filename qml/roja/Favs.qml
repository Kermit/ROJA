import Qt 4.7

Rectangle {
    id: favs
    width: content.width
    height: content.height
    color: "#000000"

    TitleBar {
        id: favsTitleBar
        text: "Ulubione"
    }

    Rectangle {
        id: favsContent
        width: parent.width
        height: parent.height - favsTitleBar.height
        color: "#000000"

        anchors.top: favsTitleBar.bottom

        Rectangle {
            id: favRoutes
            width: parent.width
            height: Math.round(parent.height * 0.1)
            color: "#111111"
            state: "hide"

            anchors.top: parent.top

            Text {
                text: "Trasy - 0 ulubionych"
                font.bold: true
                font.pointSize: 6
                color: "#FFFFFF"

                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 5
            }

            MouseArea {
                anchors.fill: parent
                onClicked:
                    if (favRoutes.state == "hide") {
                        favRoutes.state = "show";
                        favStops.state = "hide";
                        favLines.state = "hide";
                    }
            }

            states: [
                State {
                    name: "show"
                    PropertyChanges {
                        target: favRoutes;
                        height: Math.round(favsContent.height - (Math.round(favsContent.height * 0.1) * 2))
                    }
                },
                State {
                    name: "hide"
                    PropertyChanges {
                        target: favRoutes;
                        height: Math.round(favsContent.height * 0.1)
                    }
                }
            ]
        }

        Rectangle {
            id: favLines
            width: parent.width
            height: Math.round(parent.height * 0.1)
            color: "#111111"
            state: "hide"

            anchors.top: favRoutes.bottom

            Text {
                text: "Trasy - 0 ulubionych"
                font.bold: true
                font.pointSize: 6
                color: "#FFFFFF"

                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 5
            }

            MouseArea {
                anchors.fill: parent
                onClicked:
                    if (favLines.state == "hide") {
                        favLines.state = "show";
                        favStops.state = "hide";
                        favRoutes.state = "hide";
                    }
            }

            states: [
                State {
                    name: "show"
                    PropertyChanges {
                        target: favLines;
                        height: Math.round(favsContent.height - (Math.round(favsContent.height * 0.1) * 2))
                    }
                },
                State {
                    name: "hide"
                    PropertyChanges {
                        target: favLines;
                        height: Math.round(favsContent.height * 0.1)
                    }
                }
            ]
        }

        Rectangle {
            id: favStops
            width: parent.width
            height: Math.round(parent.height * 0.1)
            color: "#111111"
            state: "hide"

            anchors.top: favLines.bottom

            Text {
                text: "Trasy - 0 ulubionych"
                font.bold: true
                font.pointSize: 6
                color: "#FFFFFF"

                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 5
            }

            MouseArea {
                anchors.fill: parent
                onClicked:
                    if (favStops.state == "hide") {
                        favStops.state = "show";
                        favRoutes.state = "hide";
                        favLines.state = "hide";
                    }
            }

            states: [
                State {
                    name: "show"
                    PropertyChanges {
                        target: favStops;
                        height: Math.round(favsContent.height - (Math.round(favsContent.height * 0.1) * 2))
                    }
                },
                State {
                    name: "hide"
                    PropertyChanges {
                        target: favStops;
                        height: Math.round(favsContent.height * 0.1)
                    }
                }
            ]
        }
    }
}
