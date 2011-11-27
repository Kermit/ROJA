import Qt 4.7

Rectangle {
    width: 360
    height: 360
    color: "#000000"

    Rectangle {
        id: content
        width: parent.width
        height: parent.height - menuBar.height

        Loader {
            source: "Favs.qml"
        }
    }

    Rectangle {
        id: menuBar
        width: parent.width
        height: Math.round(parent.height * 0.15)
        y: parent.height - height

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#000000" }
            GradientStop { position: 0.49; color: "#222222" }
            GradientStop { position: 1.0; color: "#000000" }
        }
    }
}
