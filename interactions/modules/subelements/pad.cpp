#include "pad.h"

using namespace quarre;

Pad::Pad(InteractionModule *parent, uint8_t id) :
    m_state(false), r_parent(parent), m_id(id) {
    setAttribute(Qt::WA_AcceptTouchEvents);}

Pad::~Pad() {}

void Pad::paintEvent(QPaintEvent *event) {

    QBrush brush;
    QPainter painter(this);
    QPen pen(Qt::black);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);

    if(m_state) brush = QBrush(Qt::darkGreen, Qt::SolidPattern);
    else brush = QBrush(Qt::gray, Qt::SolidPattern);

    painter.fillRect(rect(), brush);
}

bool Pad::event(QEvent *event) {

    switch(event->type()) {
    case QEvent::TouchBegin: {
        m_state = 1;
        this->sendStateUpdateToParent();
        this->update();} break;
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd: {
        QList<QTouchEvent::TouchPoint> touch_points = static_cast<QTouchEvent*>(event)->touchPoints();
        foreach(const QTouchEvent::TouchPoint &touch_point, touch_points) {
            if(touch_point.state() == Qt::TouchPointReleased) {
                m_state = 0;
                this->sendStateUpdateToParent();
                this->update();}}} break;
        default: return QWidget::event(event); }
        return true;
}

void Pad::sendStateUpdateToParent() {
    r_parent->onReceivedMiscData("pad_" + m_id, m_state);}
