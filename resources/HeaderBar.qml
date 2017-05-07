import QtQuick 2.0

Rectangle {

    Text {
        id: scenario_timer
        x: 620
        y: 20
        width: 200
        height: 200
        color: "#ffffff"
        text: qsTr("00:00")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        textFormat: Text.PlainText
        font.pixelSize: 100
    }
}
