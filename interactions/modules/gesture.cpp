#include "gesture.h"
#include <QtDebug>

using namespace arbre_integral;

WhipGestureViewer::WhipGestureViewer() {}
WhipGestureViewer::~WhipGestureViewer() {}
void WhipGestureViewer::startModule() {}
void WhipGestureViewer::stopModule() {}

quarre::InteractionModuleEnum WhipGestureViewer::getModuleEnumReference() { return quarre::AI_GESTURE; }

QList<quarre::QRawSensorDataEnum> WhipGestureViewer::getQRawSensorDataRequirements() {
    QList<quarre::QRawSensorDataEnum> empty_list; return empty_list;}

QList<quarre::QGestureEnum> WhipGestureViewer::getQGestureRequirements() {
    QList<quarre::QGestureEnum> gesture_requirements;
    gesture_requirements << quarre::Whip;
}

void WhipGestureViewer::onReceivedGesture(quarre::QGestureEnum gesture) {
    qDebug() << "whip gesture received [whipgestureviewer]";}

void WhipGestureViewer::onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value) {}
void WhipGestureViewer::onReceivedMiscData(QString sender, qreal value) {}

