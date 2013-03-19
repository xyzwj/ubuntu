

function create(parent, vWidth, vHeight, top, track) {

    var component = Qt.createComponent("track.qml");

    if (component.status == Component.Ready) {
        var dynamicObject = component.createObject(parent);
        if (dynamicObject == null) {
            console.log("error creating Track");
            console.log(component.errorString());
            return false;
        }

        dynamicObject.width= vWidth;
        dynamicObject.height = vHeight;
        dynamicObject.color = "green";
        dynamicObject.text.text = track["object"]["metadata"]["title"] + " - " +track["object"]["metadata"]["title"];
        dynamicObject.x = 20;
        dynamicObject.y = top;

        // save it for later
        dynamicObject.track = track
        console.debug("here 123")

    } else {
        console.log("error loading block component");
        console.log(component.errorString());
        return false;
    }
    return component;
}
