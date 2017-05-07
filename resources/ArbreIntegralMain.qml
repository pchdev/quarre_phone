import QtQuick 2.0
import QtQuick.Controls 2.1
import Ossia 1.0 as Ossia

Rectangle {

    y: parent.height / 2
    height: parent.height / 2
    color: "#00ffffff"
    width: parent.width

    property variant aiPages
    property int currentIndex

    Ossia.Property on currentIndex {
        node: '/phone/modules/arbre-integral/read-index'
    }

    onCurrentIndexChanged: {
        main_text.text = aiPages[currentIndex]
    }

    Text {
        id: main_text
        color: "#ffffff"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.capitalization: Font.MixedCase
        font.pointSize: 20
        font.family: "Times New Roman"
        text: "L'Arbre intégral \n Donatien Garnier"
        anchors.fill: parent
    }

    Component.onCompleted: {
        var parser = new XMLHttpRequest;
        parser.open("GET", ":/json/arbre-integral.json", true);
        parser.onreadystatechange = function()
        {
            if(parser.readyState == parser.DONE)
            {
                if(parser.status == 200)
                {
                    var json_object = JSON.parse(parser.responseText);
                    loaded(json_object);
                }
            }
        }

        parser.send();
    }

    function loaded(json_object) {
        for(var i in json_object.flux.all) {
            listModel.append({"title": json_object.flux.all[i].data["title"]});
        }
    }
}
