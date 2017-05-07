import QtQuick 2.0
// NEXT ROW ------------------------------------------------

Rectangle {

    // STATES ------------------------------------------------------------------

    states: [ State { name: "no-next"; when: connect_button.pressed
            PropertyChanges { target: next_row; height: 0 }
            PropertyChanges { target: next_timer_label; font.pixelSize: 0 }},
        State { name: "no-current"; when: prefs_button.pressed
            PropertyChanges { target: next_row; height: parent.height * 0.625 }}
    ]

    // TRANSITIONS -----------------------------------------------------------

    transitions: [ Transition { from: ""; to: "no-next"; reversible: true
            ParallelAnimation { NumberAnimation { properties: "height";
                    duration: 1000; easing.type: Easing.InOutBack }}},
        Transition { from: ""; to: "no-current"; reversible: true
            ParallelAnimation { NumberAnimation { properties: "height";
                    duration: 1500; easing.type: Easing.OutBounce }}}
    ]

    Text {

        id: next_label
        y: 52
        width: 200
        height: 200
        color: "#ffffff"
        text: qsTr("NEXT")
        anchors.verticalCenterOffset: 0
        font.weight: Font.ExtraBold
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 20
        textFormat: Text.PlainText
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 60
        horizontalAlignment: Text.AlignHCenter

        // STATES ------------------------------------------------------------------

        states: [ State { name: "no-next"; when: connect_button.pressed
                PropertyChanges { target: next_label; anchors.leftMargin: -844 }},
            State { name: "no-current"; when: prefs_button.pressed
                PropertyChanges { target: next_label; anchors.verticalCenterOffset: -50 }}
        ]

        // TRANSITIONS -----------------------------------------------------------

        transitions: [ Transition { from: ""; to: "no-next"; reversible: true
                ParallelAnimation { NumberAnimation { properties: "anchors.leftMargin";
                        duration: 500; easing.type: Easing.InOutBack }}},
            Transition { from: ""; to: "no-current"; reversible: true
                ParallelAnimation { NumberAnimation { properties: "anchors.verticalCenterOffset";
                        duration: 500; easing.type: Easing.InOutBack }}}
        ]
    }

    Text {

        id: next_interaction_label
        x: 0
        y: 57
        width: 622
        height: 200
        color: "#ffffff"
        text: qsTr("interaction machin")
        anchors.verticalCenterOffset: 0
        textFormat: Text.PlainText
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 50
        anchors.left: parent.left
        font.weight: Font.ExtraBold
        horizontalAlignment: Text.AlignHCenter
        anchors.leftMargin: 234
        anchors.verticalCenter: parent.verticalCenter
    }

    Rectangle {

        id: next_circle
        x: 480
        y: 0
        width: 480
        height: 480
        color: "#19ffffff"
        radius: 240
        anchors.verticalCenterOffset: 8
        anchors.horizontalCenterOffset: 378
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        // STATES ------------------------------------------------------------------

        states: [ State { name: "no-next"; when: connect_button.pressed
                PropertyChanges { target: next_circle; width: 0; height: 0 }},
            State { name: "no-current"; when: prefs_button.pressed
                PropertyChanges { target: next_circle; anchors.horizontalCenter: 0 }}
        ]

        // TRANSITIONS -------------------------------------------------------------

        transitions: [ Transition { from: ""; to: "no-next"; reversible: true
                ParallelAnimation { NumberAnimation { properties: "width, height, font.pixelSize";
                        duration: 500; easing.type: Easing.InOutBack }}},
            Transition { from: ""; to: "no-current"; reversible: true
                ParallelAnimation { NumberAnimation { properties: "anchors.horizontalCenter";
                        duration: 1000; easing.type: Easing.InOutBack }}}
        ]

        Text {

            id: next_timer_label
            y: 52
            width: 200
            height: 200
            color: "#ffffff"
            text: qsTr("29")
            textFormat: Text.PlainText
            anchors.verticalCenterOffset: 0
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 100
            anchors.left: parent.left
            font.weight: Font.ExtraBold
            horizontalAlignment: Text.AlignHCenter
            anchors.leftMargin: 140
            anchors.verticalCenter: parent.verticalCenter

        }
    }
}
