#include "interactiondatabase.h"
#include <QtDebug>

using namespace quarre;


InteractionDatabase::InteractionDatabase() {


    // open json file
    QFile loaded_interactions(":/json/interactions.json");
    if(!loaded_interactions.open(QIODevice::ReadOnly)) {
        qDebug() << "error: couldn't open interactions.json";
    } else {
        qDebug() << "interactions.json was succesfully opened";
    }

    QJsonParseError error;
    QByteArray saved_data = loaded_interactions.readAll();
    QJsonDocument loaded_json = QJsonDocument::fromJson(saved_data, &error);

    // json doc should return an object
    if(loaded_json.isArray()) qDebug() << "file is array";
    else if(loaded_json.isObject()) qDebug() << "file is object";
    else if(loaded_json.isNull()) {
        qDebug() << "file is null";
        qDebug() << error.errorString();
    }

    // PARSING, BUILDING C++ OBJECTS

    QJsonObject main_object = loaded_json.object();

    for(int i = 0; i < main_object.count(); i++) {

        QJsonObject json_interaction = main_object["interaction_" + QString::number(i)].toObject();
        QString title = json_interaction["title"].toString();
        QString description = json_interaction["description"].toString();
        QString string_module_type = json_interaction["module_type"].toString();
        int module_enum_id = quarre::module_names2.indexOf(string_module_type);
        quarre::InteractionModuleEnum module_type = static_cast<quarre::InteractionModuleEnum>(module_enum_id);

        QJsonArray json_gesture_array = json_interaction["gesture_reponses"].toArray();
        QJsonArray json_sensor_array = json_interaction["sensor_responses"].toArray();

        QList<quarre::QGestureEnum> gesture_responses;
        QList<quarre::QRawSensorDataEnum> raw_sensor_responses;

        for(int j = 0; j < json_gesture_array.count(); j++) {
            QString json_gesture = json_gesture_array[j].toString();
            int gesture_enum_id = quarre::qgesture_names.indexOf(json_gesture);
            quarre::QGestureEnum gesture_enum = static_cast<quarre::QGestureEnum>(gesture_enum_id);
            gesture_responses << gesture_enum;
        }

        for(int j = 0; j < json_sensor_array.count(); j++) {
            QString json_sensor = json_sensor_array[j].toString();
            int sensor_enum_id = quarre::qrawsensor_names.indexOf(json_sensor);
            quarre::QRawSensorDataEnum sensor_enum = static_cast<quarre::QRawSensorDataEnum>(sensor_enum_id);
            raw_sensor_responses << sensor_enum;
        }

        quarre::Interaction *interaction = new quarre::Interaction(i, title, description, module_type, gesture_responses, raw_sensor_responses);
        am_interactions << interaction;

    }

}

InteractionDatabase::~InteractionDatabase() {}

quarre::Interaction* InteractionDatabase::getInteraction(int id) const {
    return am_interactions[id];
}

