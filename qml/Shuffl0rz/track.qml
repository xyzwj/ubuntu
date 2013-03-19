import QtQuick 2.0
import Ubuntu.Components 0.1


Rectangle{
    id: myrect
    color: "lightgreen"

    property alias text: text
    property variant track

    width: 200;
    height: 200;

    anchors {
        left: undefined
        top: undefined
        right: undefined
        bottom: undefined
    }

    MouseArea{
        anchors.fill: parent;
        onClicked: {
            parent.color = "red";
            Shuffler.play(track["object"]["stream"]["url"]);
        }
    }

    Text {
        id: text
        anchors.centerIn: parent
        text: "track-title"
    }
}
