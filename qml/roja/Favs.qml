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

        FavButton {
            id: favRoutes
            text: "Trasy - x ulubionych"

            anchors.top: favsContent.top

            MouseArea {
                id: favRoutesMA
                anchors.fill: parent
                onClicked:
                    if (favRoutes.state == "hide") {
                        favRoutes.state = "show";
                        favStops.state = "hide";
                        favLines.state = "hide";

                        favStops.anchors.topMargin = 0;
                        favLines.anchors.topMargin = 1;
                    }
            }
        }

        FavButton {
            id: favStops
            text: "Przystanki - x ulubionych"

            anchors.top: favRoutes.bottom
            anchors.topMargin: 1

            MouseArea {
                id: favStopsMA
                anchors.fill: parent
                onClicked:
                    if (favStops.state == "hide") {
                        favStops.state = "show";
                        favRoutes.state = "hide";
                        favLines.state = "hide";

                        favLines.anchors.topMargin = 0;
                        favStops.anchors.topMargin = 1;
                    }
            }
        }

        FavButton {
            id: favLines
            text: "Linie - x ulubionych"

            anchors.top: favStops.bottom
            anchors.topMargin: 1

            MouseArea {
                id: favLinesMA
                anchors.fill: parent
                onClicked:
                    if (favLines.state == "hide") {
                        favLines.state = "show";
                        favRoutes.state = "hide";
                        favStops.state = "hide";

                        favStops.anchors.topMargin = 1;
                        favLines.anchors.topMargin = 1;
                    }
            }
        }
    }
}
