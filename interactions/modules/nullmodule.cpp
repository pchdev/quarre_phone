#include "nullmodule.h"

using namespace arbre_integral;

NullModule::NullModule() {

}

NullModule::~NullModule() {}
void NullModule::startModule() {}
void NullModule::stopModule() {}
quarre::InteractionModuleEnum NullModule::getModuleEnumReference() { return quarre::AI_NULL; }
QList<quarre::QGestureEnum> NullModule::getQGestureRequirements() {
    QList<quarre::QGestureEnum> null_list; return null_list;}
QList<quarre::QRawSensorDataEnum> NullModule::getQRawSensorDataRequirements() {
    QList<quarre::QRawSensorDataEnum> null_list; return null_list;}
void NullModule::onReceivedGesture(quarre::QGestureEnum gesture) {}
void NullModule::onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value) {}
void NullModule::onReceivedMiscData(QString sender, qreal value) {}
