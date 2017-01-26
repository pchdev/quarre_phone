#include "login.h"
#include <QLayout>
#include "pad.h"

Login::Login() {
    QVBoxLayout *layout = new QVBoxLayout(this);
    quarre::Pad *pad = new quarre::Pad(this, 0);
    layout->addWidget(pad, 0, Qt::AlignCenter);
}

Login::~Login() {}
void Login::start() {}
void Login::stop() {}
QString Login::getModuleIdentifier() { return QStringLiteral("AI_LOGIN"); }
void Login::onReceivedGesture(quarre::QGestureEnum gesture) {}
void Login::onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value) {}
void Login::onReceivedCustomData(QString sender, QList<qreal> values) {
    QString pad_id = sender.split("_").at(1);
    emit sendBackData("/pads/" + pad_id, values[0], true);
}

QList<quarre::QGestureEnum> Login::getQGestureRequirements() {
    return EMPTY_QGESTUREREQLIST;
}

QList<quarre::QRawSensorDataEnum> Login::getQRawSensorDataRequirements() {
    return EMPTY_QRAWSENSORREQLIST;
}

QList<QString> Login::getCustomResponderAddresses() {
    return EMPTY_RESPADDRESSES;
}
