#include "interaction.h"

using namespace quarre;

Interaction::Interaction(int id, QString title, QString description,
                         quarre::InteractionModuleEnum module_type) :
    m_id(id),
    m_title(title),
    m_description(description),
    is_active(false),
    m_module_type(module_type) {}

Interaction::Interaction(int id, QString title, QString description,
                         quarre::InteractionModuleEnum module_type,
                         QList<quarre::QGestureEnum> gesture_responses) :
    m_id(id),
    m_title(title),
    m_description(description),
    is_active(false),
    m_module_type(module_type),
    am_gesture_responses(gesture_responses) {}

Interaction::Interaction(int id, QString title, QString description,
                         quarre::InteractionModuleEnum module_type,
                         QList<quarre::QGestureEnum> gesture_responses,
                         QList<quarre::QRawSensorDataEnum> raw_sensor_responses) :
    m_id(id),
    m_title(title),
    m_description(description),
    is_active(false),
    m_module_type(module_type),
    am_gesture_responses(gesture_responses),
    am_raw_sensor_responses(raw_sensor_responses) {}

Interaction::~Interaction() {}
