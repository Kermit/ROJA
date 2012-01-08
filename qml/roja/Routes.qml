import Qt 4.7

Rectangle {
    property string page : "Main"

    id: routesBox
    objectName: "routesBox"
    width: content.width
    height: content.height
    color: "#000000"

    TitleBar {
        id: routesTitleBar
        objectName: "routesTitleBar"
        text: "Wyszukiwanie tras"

        BackButton {
            objectName: "routesBackButton"
            page: routesBox.page
            visible: false
        }

        Image {
            signal searchButtonClicked()

            id: chooseStopSearchButton
            objectName: "chooseStopSearchButton"
            source: "qrc:/images/lupaIcon.png"
            smooth: true
            height: parent.height - 4
            width: height
            visible: false
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 5
            anchors.right: parent.right

            MouseArea {
                id: backMA
                anchors.fill: parent
                onClicked: chooseStopSearchButton.searchButtonClicked()
            }
        }
    }

    Search {
        id: chooseStopSearch
        objectName: "chooseStopSearch"
        anchors.top: routesTitleBar.bottom
    }

    Rectangle {
        id: searchBox
        objectName: "searchBox"

        width: parent.width
        height: parent.height - routesTitleBar.height
        color: "#000000"

        visible: true
        anchors.top: routesTitleBar.bottom

        Rectangle {
            signal clicked(bool startstop)
            property string text : "Przystanek początkowy"

            id: startStop
            objectName: "startStop"
            width: Math.round(parent.width * 0.95)
            height: Math.round(menuBar.height * 0.6)
            color: "#FFFFFF"
            radius: 3

            anchors.topMargin: 5
            anchors.top: searchBox.top
            anchors.leftMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                font.pointSize: 7
                anchors.centerIn: parent
                text: parent.text
            }

            MouseArea {
                anchors.fill: parent
                onClicked: startStop.clicked(true)
            }
        }

        Rectangle {
            signal clicked(bool startstop)
            property string text : "Przystanek końcowy"

            id: endStop
            objectName: "endStop"

            width: Math.round(parent.width * 0.95)
            height: Math.round(menuBar.height * 0.6)
            color: "#FFFFFF"
            radius: 3

            anchors.topMargin: 5
            anchors.top: startStop.bottom
            anchors.leftMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                font.pointSize: 7
                anchors.centerIn: parent
                text: parent.text
            }

            MouseArea {
                anchors.fill: parent
                onClicked: endStop.clicked(false)
            }
        }

        Rectangle {
            property bool przesiadka : false

            id: przesiadkaButton
            objectName: "przesiadkaButton"

            width: Math.round(parent.width * 0.45)
            height: Math.round(menuBar.height * 0.6)

            border.color: "#FFFFFF"
            border.width: 1
            color: "#000000"

            anchors.top: endStop.bottom
            anchors.topMargin: 10
            anchors.leftMargin: 5

            Text {
                anchors.centerIn: parent
                font.pointSize: 6
                color: "#FFFFFF"
                text:
                    if (przesiadkaButton.przesiadka)
                    {
                        "Z przesiadką"
                    }
                    else
                    {
                        "Bez przesiadki"
                    }
            }

            MouseArea {
                id: przesiadkaMA
                anchors.fill: parent
                onClicked: przesiadkaButton.przesiadka = !przesiadkaButton.przesiadka
            }

            states: State {
                    name: "changeColor"
                    when:  przesiadkaMA.pressed == true
                    PropertyChanges {
                            target: przesiadkaButton
                            color: "#ff8e00"
                    }
            }
        }

        Rectangle {
            signal clicked()

            id: routesSearchButton
            objectName: "routesSearchButton"

            width: Math.round(parent.width * 0.45)
            height: Math.round(menuBar.height * 0.6)

            border.color: "#FFFFFF"
            border.width: 1
            color: "#000000"

            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.top: endStop.bottom
            anchors.topMargin: 10

            Text {
                anchors.centerIn: parent
                font.pointSize: 6
                color: "#FFFFFF"
                text: "Szukaj"
            }

            MouseArea {
                id: routesSerachButtonMA
                anchors.fill: parent
                onClicked: {
                    routesSearchButton.clicked()
                }
            }

            states: State {
                    name: "changeColor"
                    when:  routesSerachButtonMA.pressed == true
                    PropertyChanges {
                            target: routesSearchButton
                            color: "#ff8e00"
                    }
            }
        }
    }

    Rectangle {
        id: searchResultsBox
        objectName: "searchResultsBox"

        width: parent.width
        height: parent.height - routesTitleBar.height
        color: "#000000"

        visible: false
        anchors.top: routesTitleBar.bottom

        ListView {
            signal indexChanged(int routedetailsid, string routeids, string route)

            id: routeListView
            objectName: "routeListView"
            anchors.fill: parent
            model: routesModel
            clip: true
            delegate: RoutesDelegate {}
            header:
                Rectangle {
                    height: 1
                    width: parent.width
                    color: "#FFFFFF"
                }
        }
    }

    Rectangle {
        id: searchDetailResultsBox
        objectName: "searchDetailResultsBox"

        width: parent.width
        height: parent.height - routesTitleBar.height
        color: "#000000"

        visible: false
        anchors.top: routesTitleBar.bottom

        ListView {
            signal indexChanged(int routedetailsid, string routeids, string route)

            id: routeDetailsListView
            objectName: "routeDetailsListView"
            anchors.fill: parent
            model: routesDetailModel
            clip: true
            delegate: RoutesDelegate {}
            header:
                Rectangle {
                    height: 1
                    width: parent.width
                    color: "#FFFFFF"
                }
        }
    }

    Rectangle {
        id: routesTimetable
        objectName: "routesTimetable"

        width: parent.width
        height: parent.height - routesTitleBar.height
        color: "#000000"

        visible: false
        anchors.top: routesTitleBar.bottom

        ListView {
            id: timetableListView
            objectName: "routesTimetableList"
            anchors.fill: parent
            model: routesTimetableModel
            clip: true
            delegate: TimetableDelegate {}
        }
    }

    Rectangle {
        id: chooseStopBox
        objectName: "chooseStopBox"

        width: parent.width
        height: parent.height - routesTitleBar.height - chooseStopSearch.height
        color: "#000000"

        visible: false
        anchors.top: chooseStopSearch.bottom

        ListView {
            signal indexChanged(string stopname, int stopid)

            id: chooseStopList
            objectName: "chooseStopList"
            anchors.fill: parent
            model: chooseStopModel
            clip: true
            delegate: ChooseStopDelegate {}
            header:
                Rectangle {
                    height: 1
                    width: parent.width
                    color: "#FFFFFF"
                }
        }
    }

    Text {
        id: communicateText
        objectName: "communicateText"
        text: "Szukam, proszę czekać"

        color: "red"
        font.pointSize: 8
        font.bold: true

        anchors.horizontalCenter: parent.horizontalCenter
        y: (parent.height/2 + 10)
        visible: false
        z: 10
    }
}
