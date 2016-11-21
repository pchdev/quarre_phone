#include "introduction.h"

#include <QLayout>
#include <QLabel>

using namespace arbre_integral;

Introduction::Introduction(){
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *intro_title = new QLabel("ARBRE_INTEGRAL_INTRO");
    layout->addWidget(intro_title, 0, Qt::AlignCenter); }

Introduction::~Introduction() {}
quarre::InteractionModuleEnum Introduction::getModuleEnumReference() { return quarre::AI_INTRODUCTION; }
void Introduction::startModule() {}
void Introduction::stopModule() {}
QList<quarre::QGestureEnum> Introduction::getQGestureRequirements() {}
QList<quarre::QRawSensorDataEnum> Introduction::getQRawSensorDataRequirements() {}
void Introduction::onReceivedGesture(quarre::QGestureEnum gesture) {}
void Introduction::onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value) {}
void Introduction::onReceivedMiscData(QString sender, qreal value) {}


