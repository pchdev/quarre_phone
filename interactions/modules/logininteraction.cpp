#include "logininteraction.h"


using namespace arbre_integral;

LoginInteraction::LoginInteraction() : is_active(false) {}
LoginInteraction::~LoginInteraction() {}

void LoginInteraction::onReceivedGesture(quarre::QGestureEnum gesture) {}
void LoginInteraction::onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value){}
void LoginInteraction::startModule() { is_active = true; }
void LoginInteraction::stopModule() { is_active = false; }
quarre::InteractionModuleEnum LoginInteraction::getModuleEnumReference() { return quarre::AI_LOGIN; }
QList<quarre::QRawSensorDataEnum> LoginInteraction::getQRawSensorDataRequirements() {}
QList<quarre::QGestureEnum> LoginInteraction::getQGestureRequirements() {
    QList<quarre::QGestureEnum> gesture_requirements;
    gesture_requirements << quarre::Whip;
    return gesture_requirements; }

void LoginInteraction::paintEvent(QPaintEvent *event) {}
bool LoginInteraction::event(QEvent *event) {}
void LoginInteraction::onReceivedMiscData(QString sender, qreal value) {}
