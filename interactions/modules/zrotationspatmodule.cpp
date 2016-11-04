#include "zrotationspatmodule.h"

ZRotationSpatModule::ZRotationSpatModule(quarre::Control *controller, qreal angle_offset) :
    m_angle_offset(angle_offset) {
    setController(controller);
}

ZRotationSpatModule::~ZRotationSpatModule() {}

quarre::InteractionModuleEnum ZRotationSpatModule::getModuleEnumReference() {
    return quarre::Z_Rotation_spat;
}

void ZRotationSpatModule::refreshView() {
    this->update();
}

void ZRotationSpatModule::paintEvent(QPaintEvent *event) {

    // init
    float w = width();
    QPainter painter(this);
    painter.translate(0, w/10);
    QPen pen(Qt::darkGray);
    pen.setWidthF(w*0.002);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);

    // arc drawing
    QRectF rect(0, 0, w, w);
    QPainterPath path;
    QPoint center(w, w/2);
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

    // translate & rotate arrow position
    painter.save();
    painter.translate(w/2, w/2);
    painter.rotate(m_azimuth);
    painter.drawConvexPolygon(arrow, 7);
    painter.restore();

}

void ZRotationSpatModule::onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value) {
    if(sensor == quarre::Rotation_z) {
        m_azimuth = value;
        this->update();
    }
}
