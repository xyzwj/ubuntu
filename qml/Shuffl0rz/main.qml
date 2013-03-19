import QtQuick 2.0
import Ubuntu.Components 0.1
import "TrackView.js" as TrackView

MainView {
    objectName: "mainView"
    applicationName: "Shuffl0rz"
    id: root

    width: units.gu(60)
    height: units.gu(80)

    property real margins: units.gu(2)
    property real buttonWidth: units.gu(9)

    Connections {
        target: Shuffler
        onChannelReady: {
            console.log("channel arrived");
            for(var k in tracks) {
                console.debug("there: " + k)
                TrackView.create(root, 300, 100, k*110, tracks[k]);
            }
        }
    }

    Label {
       id: title
       ItemStyle.class: "title"
       text: i18n.tr("Shuffl0rz for Ubuntuz NIna")
       height: contentHeight + root.margins
       anchors {
           left: parent.left
           right: parent.right
           top: parent.top
       }
    }

    Text {
        id: channelKey
        anchors.centerIn: parent
        color: "white"
        text: "indie"
    }

    Rectangle {
        id: button

        width: 100; height: 40
        anchors.right: parent.right;
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 20

        radius: 6
        color: "gray"

        Text {
            anchors.centerIn: parent
            text: "Go"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.debug("button clicked");
                Shuffler.channel("indie");
            }
        }
    }

}
