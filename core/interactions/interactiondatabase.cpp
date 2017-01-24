#include "interactiondatabase.h"
#include <QtDebug>
#include <QCoreApplication>
#include <QDir>

using namespace quarre;

#define JSON_NAMESPACE "ARBRE_INTEGRAL"

InteractionDatabase::~InteractionDatabase() {}
quarre::Interaction* InteractionDatabase::getInteraction(int id) const {return am_interactions[id];}
InteractionDatabase::InteractionDatabase() {

    // get android assets path
    QString application_path(QCoreApplication::applicationDirPath());
    QDir dir(path);


}

void InteractionDatabase::loadInteractionNamespace(QString json_file_name) {
    // open json file
    QFile loaded_interactions("assets:/" + json_file_name + ".json");
    if(!loaded_interactions.open(QIODevice::ReadOnly)) {
        qDebug() << "error: couldn't open .json namespace file";
    } else {  qDebug() << json_file_name << ".json namespace file succesfully loaded!";}

    QJsonParseError error;
    QByteArray saved_data = loaded_interactions.readAll();
    QJsonDocument loaded_json = QJsonDocument::fromJson(saved_data, &error);
    if(loaded_json.isNull()) qDebug() << error.errorString();

    // PARSING, LOADING C++ OBJECTS
    QJsonObject main_object = loaded_json.object();
    QJsonArray chosen_namespace = main_object[JSON_NAMESPACE].toArray();

    // EACH NAMESPACE CONTAINS AN ARRAY OF INTERACTIONS
    for(int i = 0; i < chosen_namespace.count(); i++) {

        QJsonObject interaction = chosen_namespace[i].toObject();
        QString title = interaction["title"].toString();
        QString description = interaction["description"].toString();
        QString module_id = interaction["module_id"].toString();
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

        quarre::Interaction *interaction_object = new quarre::Interaction(i, title, description, module_id, gesture_responses, sensor_responses);
        am_interactions << interaction_object;
    }

}

