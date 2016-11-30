#include "loopcontrol.h"
#include <QLayout>

using namespace arbre_integral;

LoopControl::LoopControl(quarre::InteractionModule *viewer) {

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *layout_pads = new QHBoxLayout;
    quarre::Pad *start_pad = new quarre::Pad(this);
    quarre::Pad *stop_pad = new quarre::Pad(this, 1);
    start_pad->setFixedSize(100, 100);
    stop_pad->setFixedSize(100, 100);
    layout_pads->addWidget(start_pad);
    layout_pads->addWidget(stop_pad);
    layout->addLayout(layout_pads);
    layout->addWidget(viewer, 0, Qt::AlignCenter);
}

LoopControl::~LoopControl() {}
quarre::InteractionModuleEnum LoopControl::getModuleEnumReference() { return quarre::AI_LOOPCONTROL; }

QList<quarre::QRawSensorDataEnum> LoopControl::getQRawSensorDataRequirements() {
    QList<quarre::QRawSensorDataEnum> empty_list; return empty_list;
}
QList<quarre::QGestureEnum> LoopControl::getQGestureRequirements() {
    QList<quarre::QGestureEnum> empty_list; return empty_list;
}

void LoopControl::startModule() {}
void LoopControl::stopModule() {}
void LoopControl::onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value) {}
void LoopControl::onReceivedGesture(quarre::QGestureEnum gesture) {}

void LoopControl::onReceivedMiscData(QString sender, qreal value) {
    if(sender == "pad_0") {
        if(value == 1) r_control->processModuleCallback("/loop", 1, true);}
    else if(sender == "pad_1") {
        if(value == 1) r_control->processModuleCallback("/loop", 0, true);}
}


