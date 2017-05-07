import QtQuick 2.0
import QtQuick.Controls 2.1

Rectangle {

    id: upper_view
    width: parent.width
    height: parent.height / 2
    color: "#b3000000"
    border.color: "#66000000"
    border.width: 0

    HeaderBar {
        id: header_bar
        width: parent.width
        height: parent.height * 0.1875
        color: "#4c000000"
        border.color: "#66000000"
    }

    NextInteractionView {
        id: next_interaction_view
        y: parent.height * 0.1875
        width: parent.width
        height: parent.height * 0.25
        color: "#33001a09"
    }

    CurrentInteractionView {
        id: current_interaction_view
        y: parent.height * 0.4375
        width: parent.width
        height: parent.height * 0.375
        color: "#4c953434"
    }

}

