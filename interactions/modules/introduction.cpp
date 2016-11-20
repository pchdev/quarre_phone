#include "introduction.h"

#include <QLayout>
#include <QLabel>

using namespace arbre_integral;

Introduction::Introduction(){

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *intro_title = new QLabel("ARBRE_INTEGRAL_INTRO");

    layout->addWidget(intro_title, 0, Qt::AlignCenter);

}

Introduction::~Introduction() {}

void Introduction::startModule() {}
void Introduction::stopModule() {}
quarre::InteractionModuleEnum Introduction::getModuleEnumReference() { return quarre::AI_INTRODUCTION; }
QList<quarre::QGestureEnum> Introduction::getQGestureRequirements() {}
QList<quarre::QRawSensorDataEnum> Introduction::getQRawSensorDataRequirements() {}
void Introduction::onReceivedGesture(quarre::QGestureEnum gesture) {}
void Introduction::onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value) {}

