#include "interactiondatabase.h"
#include <QtDebug>

using namespace quarre;

#define JSON_NAMESPACE "ARBRE_INTEGRAL"

InteractionDatabase::~InteractionDatabase() {}
quarre::Interaction* InteractionDatabase::getInteraction(int id) const {return am_interactions[id];}
InteractionDatabase::InteractionDatabase() {

    // open json file
    QFile loaded_interactions(":/json/interactions.json");
    if(!loaded_interactions.open(QIODevice::ReadOnly)) {
        qDebug() << "error: couldn't open interactions.json";
    } else {  qDebug() << "interactions.json succesfully loaded!";}

    QJsonParseError error;
    QByteArray saved_data = loaded_interactions.readAll();
    QJsonDocument loaded_json = QJsonDocument::fromJson(saved_data, &error);
    if(loaded_json.isNull()) qDebug() << error.errorString();

    // PARSING, BUILDING C++ OBJECTS
    QJsonObject main_object = loaded_json.object();
    QJsonArray chosen_namespace = main_object[JSON_NAMESPACE].toArray();

    // EACH NAMESPACE CONTAINS AN ARRAY OF INTERACTIONS
    for(int i = 0; i < chosen_namespace.count(); i++) {

        QJsonObject interaction = chosen_namespace[i].toObject();
        QString title = interaction["title"].toString();
        qDebug() << title;
        QString description = interaction["description"].toString();
        QString string_module_type = interaction["module_type"].toString();
        int module_enum_id = quarre::module_names.indexOf(string_module_type);
        quarre::InteractionModuleEnum module_type = static_cast<quarre::InteractionModuleEnum>(module_enum_id);
        QJsonArray gesture_array = interaction["gesture_responses"].toArray();
        QJsonArray sensor_array = interaction["sensor_responses"].toArray();

        QList<quarre::QGestureEnum> gesture_responses;
        QList<quarre::QRawSensorDataEnum> sensor_responses;

        // parsing gesture requirements
        for(int j = 0; j < gesture_array.count(); j++) {
            QString gesture = gesture_array[j].toString();
            int gesture_enum_id = quarre::qgesture_names.indexOf(gesture);
            quarre::QGestureEnum gesture_enum = static_cast<quarre::QGestureEnum>(gesture_enum_id);
            gesture_responses << gesture_enum;
        }

        // parsing sensor requirements
        for(int j = 0; j < sensor_array.count(); j++) {
            QString sensor = sensor_array[j].toString();
            int sensor_enum_id = quarre::qrawsensor_names.indexOf(sensor);
            quarre::QRawSensorDataEnum sensor_enum = static_cast<quarre::QRawSensorDataEnum>(sensor_enum_id);
            sensor_responses << sensor_enum;
        }

        quarre::Interaction *interaction_object = new quarre::Interaction(i, title, description, module_type, gesture_responses, sensor_responses);
        am_interactions << interaction_object;
    }

}

