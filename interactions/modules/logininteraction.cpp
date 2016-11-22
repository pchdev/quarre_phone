#include "logininteraction.h"
#include <QLayout>


using namespace arbre_integral;

LoginInteraction::LoginInteraction() : is_active(false) {

    QVBoxLayout *layout = new QVBoxLayout(this);
    quarre::Pad *pad = new quarre::Pad(this, 0);
    layout->addWidget(pad, 0, Qt::AlignCenter);

}

LoginInteraction::~LoginInteraction() {}

void LoginInteraction::onReceivedGesture(quarre::QGestureEnum gesture) {}
void LoginInteraction::onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value){}
void LoginInteraction::startModule() { is_active = true; }
void LoginInteraction::stopModule() { is_active = false; }
quarre::InteractionModuleEnum LoginInteraction::getModuleEnumReference() { return quarre::AI_LOGIN; }
QList<quarre::QRawSensorDataEnum> LoginInteraction::getQRawSensorDataRequirements() {
    QList<quarre::QRawSensorDataEnum> empty_list; return empty_list;
}
QList<quarre::QGestureEnum> LoginInteraction::getQGestureRequirements() {
    QList<quarre::QGestureEnum> empty_list; return empty_list;
}

void LoginInteraction::paintEvent(QPaintEvent *event) {}
bool LoginInteraction::event(QEvent *event) {}

void LoginInteraction::onReceivedMiscData(QString sender, qreal value) {
    QString pad_id = sender.split("_").at(1);
    r_control->processModuleCallback("/pads/" + pad_id, value, true);
}
