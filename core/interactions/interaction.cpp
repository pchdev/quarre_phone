#include "interaction.h"

using namespace quarre;

Interaction::Interaction(int id, QString title, QString description,
                         QString module_name) :
    m_id(id),
    m_title(title),
    m_description(description),
    is_active(false),
    m_module_id(module_name) {}

Interaction::Interaction(int id, QString title, QString description,
                         QString module_name,
                         QList<quarre::QGestureEnum> gesture_responses) :
    m_id(id),
    m_title(title),
    m_description(description),
    is_active(false),
    m_module_id(module_name),
    am_gesture_responses(gesture_responses) {}

Interaction::Interaction(int id, QString title, QString description,
                         QString module_name,
                         QList<quarre::QGestureEnum> gesture_responses,
                         QList<quarre::QRawSensorDataEnum> raw_sensor_responses) :
    m_id(id),
    m_title(title),
    m_description(description),
    is_active(false),
    m_module_id(module_name),
    am_gesture_responses(gesture_responses),
    am_raw_sensor_responses(raw_sensor_responses) {}

Interaction::~Interaction() {}
void Interaction::setCurrentLength(int length) {m_current_length = length;}
void Interaction::setActive(bool active) {is_active = active;}
int Interaction::getId() const {return m_id;}
QString Interaction::getTitle() const {return m_title;}
QString Interaction::getDescription() const {return m_description;}
int Interaction::getCurrentLength() const {return m_current_length;}
QString Interaction::getModuleId() const {return m_module_id;}
bool Interaction::isActive() const {return is_active;}
QList<quarre::QGestureEnum> Interaction::getGesturePollingRequirements() const {return am_gesture_responses;}
QList<quarre::QRawSensorDataEnum> Interaction::getRawSensorDataPollingRequirements() const {return am_raw_sensor_responses;}
