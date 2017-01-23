#ifndef INTERACTION_H
#define INTERACTION_H

#include <QString>

#include "modulemanager.h"
#include "../../plugins/quarreplugininterface.h"

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

    int getId() const;
    QString getTitle() const;
    QString getDescription() const;
    int getCurrentLength() const;
    quarre::InteractionModuleEnum getModuleId() const;
    QList<quarre::QGestureEnum> getGesturePollingRequirements() const;
    QList<quarre::QRawSensorDataEnum> getRawSensorDataPollingRequirements() const;
    bool isActive() const;

    void setCurrentLength(int length);
    void setActive(bool active);

private:
    int m_id;
    QString m_title;
    QString m_description;
    int m_current_length;
    bool is_active;
    quarre::InteractionModuleEnum m_module_type;
    QList<quarre::QGestureEnum> am_gesture_responses;
    QList<quarre::QRawSensorDataEnum> am_raw_sensor_responses;
};

}

#endif // INTERACTION_H
