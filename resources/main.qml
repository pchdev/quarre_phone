import QtQuick 2.7
import QtQuick.Window 2.2
import Ossia 1.0 as Ossia

Window {

    id: root
    //width: Screen.desktopAvailableWidth
    //height: Screen.desktopAvailableHeight

    width: 1080
    height: 1920

    color: "#ffffff"
    visible: true
    title: qsTr("quarrè-phone-2")

    Image {
        id: quarre_background
        antialiasing: true
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "quarre.jpg"
    }

    PrefsWindow {
        visible: true
    }

    HeaderBar {
    }

    InfoView {

    }

    // OSC ------------------------------------------------

    Component.onCompleted: {
        Ossia.SingleDevice.openOSCQueryServer(5678, 1234)
        Ossia.SingleDevice.recreate(root)
        console.log("oscquery opened");
        //oscquery_server.openOSCQueryServer(oscquery_server.address, oscquery_server.localPort);
        //oscquery_server.remap(root);
    }

    property variant incomingInteraction
    property int nextInteractionBegin
    property int currentInteractionEnd

    /*Ossia.Property on incomingInteraction {
        node: "/phone/interactions/next/incoming"
    }

    Ossia.Property on nextInteractionBegin {
        node: "/phone/interactions/next/begin"
    }

    Ossia.Property on currentInteractionEnd {
        node: "/phone/interactions/current/end"
    }*/

    onIncomingInteractionChanged: {
        if(incomingInteraction.length === 3)
        {

        }
    }

    onNextInteractionBeginChanged: {
        console.log(nextInteractionBegin)
    }

    onCurrentInteractionEndChanged: {
        console.log(currentInteracionEnd)
    }


    // LOWER VIEW ------------------------------------------------

    Rectangle {

        id: lower_view
        y: parent.height / 2
        width: parent.width
        height: parent.height / 2
        color: "#e60b0909"
        border.width: 0
        border.color: "#000000"

        //ArbreIntegralMain {}
    }
}
