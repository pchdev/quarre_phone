import QtQuick 2.0

Rectangle {

    states: [ State { name: "no-next"; when: connect_button.pressed
            PropertyChanges { target: current_row;
                y: parent.height * 0.1875; height: parent.height * 0.625 }},
        State { name: "no-current"; when: prefs_button.pressed
            PropertyChanges { target: current_row; y: parent.height; height: 0 }}
    ]


    transitions: [ Transition {
            from: ""; to: "no-next"; reversible: true
            ParallelAnimation { NumberAnimation { properties: "y, height";
                    duration: 1250; easing.type: Easing.InOutBack }}},
        Transition { from: ""; to: "no-current"; reversible: true
            ParallelAnimation { NumberAnimation { properties: "y, height";
                    duration: 1000; easing.type: Easing.InOutBack }}}
    ]

    Rectangle {
        id: current_circle
        x: 480
        y: 0
        width: 480
        height: 480
        color: "#99070606"
        radius: 240
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        Text {
            id: current_timer_label
            y: 52
            width: 200
            height: 200
            color: "#ffffff"
            text: qsTr("60")
            anchors.verticalCenterOffset: 0
            textFormat: Text.PlainText
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 140
            anchors.left: parent.left
            font.weight: Font.ExtraBold
            horizontalAlignment: Text.AlignHCenter
            anchors.leftMargin: 140
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Rectangle {
        id: current_info
        y: parent.height * 0.8125
        width: parent.width
        height: parent.height * 0.1875
        color: "#4c713232"

        Text {
            id: current_interaction_label
            x: 8
            y: 57
            width: 680
            height: 240
            color: "#ffffff"
            text: qsTr("interaction machin")
            textFormat: Text.PlainText
            anchors.verticalCenterOffset: 0
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 60
            //anchors.left: next_label.right
            font.weight: Font.ExtraBold
            horizontalAlignment: Text.AlignHCenter
            anchors.leftMargin: 150
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            id: current_descr_label
            x: 694
            y: 61
            width: 738
            height: 240
            color: "#ffffff"
            text: qsTr("description de l'interaction")
            font.family: "Arial"
            textFormat: Text.AutoText
            anchors.verticalCenterOffset: 0
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 40
            //anchors.left: next_label.right
            font.weight: Font.Normal
            horizontalAlignment: Text.AlignHCenter
            anchors.leftMargin: 150
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
