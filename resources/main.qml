import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

Window {

    id: mainwindow
    //width: Screen.desktopAvailableWidth
    //height: Screen.desktopAvailableHeight

    width: 1440
    height: 2560

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

    // UPPER VIEW ------------------------------------------------

    Rectangle {
        id: upper_view
        width: parent.width
        height: parent.height / 2
        color: "#b3000000"
        border.color: "#66000000"
        border.width: 0

        Rectangle {
            id: info_row
            width: parent.width
            height: parent.height * 0.1875
            color: "#4c000000"
            border.color: "#66000000"

            Button {
                id: connect_button
                y: 100
                width: 200
                height: 120
                text: qsTr("CONNECT")
                anchors.left: parent.left
                anchors.leftMargin: 92
                anchors.verticalCenter: parent.verticalCenter
            }

            Button {
                id: prefs_button
                x: 1220
                y: 100
                width: 200
                height: 120
                text: qsTr("PREFS")
                anchors.right: parent.right
                anchors.rightMargin: 120
                anchors.verticalCenter: parent.verticalCenter
            }

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

        // NEXT ROW ------------------------------------------------

        Rectangle {

            id: next_row
            y: parent.height * 0.1875
            width: parent.width
            height: parent.height * 0.25
            color: "#33001a09"

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

        // CURRENT ROW ------------------------------------------------

        Rectangle {

            id: current_row
            y: parent.height * 0.4375
            width: parent.width
            height: parent.height * 0.375
            color: "#4c953434"

            // STATES ------------------------------------------------------------------

            states: [ State { name: "no-next"; when: connect_button.pressed
                    PropertyChanges { target: current_row;
                        y: parent.height * 0.1875; height: parent.height * 0.625 }},
                State { name: "no-current"; when: prefs_button.pressed
                    PropertyChanges { target: current_row; y: parent.height; height: 0 }}
            ]

            // TRANSITIONS -------------------------------------------------------------

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
                anchors.left: next_label.right
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
                anchors.left: next_label.right
                font.weight: Font.Normal
                horizontalAlignment: Text.AlignHCenter
                anchors.leftMargin: 150
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Rectangle {
        id: lower_view
        y: parent.height / 2
        width: parent.width
        height: parent.height / 2
        color: "#e60b0909"
        border.width: 0
        border.color: "#000000"
    }
}
