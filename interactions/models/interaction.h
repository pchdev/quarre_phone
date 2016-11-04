#ifndef INTERACTION_H
#define INTERACTION_H

#include <QString>
#include "../modules/modulemanager.h"
#include "../../sensors/sensormanager.h"
#include "../../_fwd/fwd_enum.h"

namespace quarre {

class Interaction {

public:
    Interaction(int id, QString title, QString description,
                quarre::InteractionModuleEnum module_type);
    Interaction(int id, QString title, QString description,
                quarre::InteractionModuleEnum module_type,
                QList<quarre::QGestureEnum> gesture_responses);
    Interaction(int id, QString title, QString description,
                quarre::InteractionModuleEnum module_type,
                QList<quarre::QGestureEnum> gesture_responses,
                QList<quarre::QRawSensorDataEnum> raw_sensor_responses);
    ~Interaction();

private:
    int m_id;
    QString m_title;
    QString m_description;
    bool is_active;
    quarre::InteractionModuleEnum m_module_type;
    QList<quarre::QGestureEnum> am_gesture_responses;
    QList<quarre::QRawSensorDataEnum> am_raw_sensor_responses;
};

}

#endif // INTERACTION_H
