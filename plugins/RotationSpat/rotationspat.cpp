#include "rotationspat.h"
#include <QtDebug>


RotationSpat::RotationSpat() : m_azimuth(0.0) {}
RotationSpat::~RotationSpat() {}

void RotationSpat::start() {}
void RotationSpat::stop() {}

QString RotationSpat::getModuleIdentifier() { return "ROTATION_SPAT"; }
QList<quarre::QGestureEnum> RotationSpat::getQGestureRequirements() { return EMPTY_QGESTUREREQLIST; }
QList<QString> RotationSpat::getCustomResponderAddresses() { return EMPTY_RESPADDRESSES; }

QList<quarre::QRawSensorDataEnum> RotationSpat::getQRawSensorDataRequirements() {
    QList<quarre::QRawSensorDataEnum> requirements;
    requirements << quarre::Rotation_z;
    return requirements;
}

void RotationSpat::paintEvent(QPaintEvent *event) {
    float w = width();
    QPainter painter(this);
    painter.translate(0, 100);
    QPen pen(Qt::darkGray);
    pen.setWidthF(w*0.002);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);

    // arc drawing
    QRectF rect(0,0,w,w);
    QPainterPath path;
    QPoint center(w,w/2);
    path.moveTo(center);
    path.arcTo(rect, 0, 180);
    painter.strokePath(path, pen);

    // draw arrow
    QBrush brush(Qt::darkGray, Qt::SolidPattern);
    painter.setBrush(brush);
    QPointF origin(w/2, 0.0);
    float arrow_size = w*0.05;
    static const QPointF arrow[7] = {
        QPointF(origin.x(), origin.y()),
        QPointF(origin.x() - arrow_size, origin.y() + arrow_size),
        QPointF(origin.x() - arrow_size, origin.y() + arrow_size/2.0),
        QPointF(origin.x() - arrow_size*2.0, origin.y() + arrow_size/2.0),
        QPointF(origin.x() - arrow_size*2.0, origin.y() - arrow_size/2.0),
        QPointF(origin.x() - arrow_size, origin.y() - arrow_size/2.0),
        QPointF(origin.x() - arrow_size, origin.y() - arrow_size)
    };

    //translate & rotate arrow position
    painter.save();
    painter.translate(w/2, w/2);
    painter.rotate(m_azimuth);
    painter.drawConvexPolygon(arrow, 7);
    painter.restore();
}

void RotationSpat::onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value) {
    if(sensor == quarre::Rotation_z) {
        m_azimuth = value;
        this->update();
    }
}

void RotationSpat::onReceivedGesture(quarre::QGestureEnum gesture) {}
void RotationSpat::onReceivedCustomData(QString sender, QList<qreal> values) {}



