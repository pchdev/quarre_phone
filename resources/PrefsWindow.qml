import QtQuick 2.0
import QtQuick.Window 2.0

Window {

    height: 1920
    width: 1080

    FontLoader {
        id: lato_thin
        name: "lato_thin"
        source: "qrc:/fonts/lato/Lato-Light.ttf"
    }

    Image {

        id: quarre_background
        antialiasing: true
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "quarre.jpg"

        Rectangle {
            color: "#cc070606"
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.fill: parent

            Rectangle {
                id: rectangle
                x: 292
                y: 710
                width: 500
                height: 500
                color: "#66000000"
                radius: 250
            }

            Text {
                id: text1
                x: 403
                y: 286
                color: "#ffffff"
                text: qsTr("quarrè")
                font.capitalization: Font.AllUppercase
                font.pixelSize: 70
                font.family: lato_thin.name
            }
        }

        Text {
            x: 312
            y: 717
            color: "#ffffff"
            text: "Awaiting \n connection..."
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 79
            font.family: lato_thin.name
        }
    }


}

