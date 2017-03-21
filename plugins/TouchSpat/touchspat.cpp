#include "touchspat.h"
#include <math.h>

#define VIEW_REFRESH_RATE 30
#define TOUCH_AREA_SIZE 50
#define NUM_SPEAKERS 8
#define NUM_SOURCES 2


TouchSpat::TouchSpat() : m_polling_timer(new QTimer(this)), active(false) {
    this->setFixedSize(288 * 0.95, 288 * 0.95);
    setAttribute(Qt::WA_AcceptTouchEvents);
    this->initSourcesPositions();
    this->initSpeakerPositions();
    QObject::connect(m_polling_timer, SIGNAL(timeout()), this, SLOT(update()));
}

TouchSpat::~TouchSpat() {}

void TouchSpat::initSpeakerPositions() {
    for(int i = 0; i < NUM_SPEAKERS; i++) {
        qreal global = i/NUM_SPEAKERS * 2.f * M_PI + (M_PI/NUM_SPEAKERS);
        qreal x = sin(global) / 2.f;
        qreal y = cos(global) / 2.f;
        m_speakers_coordinates.push_back(QPointF((x+1)/2.f * width(), (y+1)/2.f) * width());
    }
}

void TouchSpat::initSourcesPositions() {
    m_sources_coordinates.push_back(QPointF(width()*0.25, height()*0.5));
    m_sources_coordinates.push_back(QPointF(width()*0.75, height()*0.5));
}

void TouchSpat::paintEvent(QPaintEvent *event) {

    qreal w = width();
    QPainter painter(this);

    // draw main ellipse
    QPen pen(Qt::darkGray);
    pen.setWidthF(1.5);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);
    painter.drawEllipse(QPointF(w/2, w/2), w/2, w/2);

    // draw grid lines
    pen.setWidthF(0.6);
    painter.setPen(pen);
    painter.drawLine(w/2, 0, w/2, w);
    painter.drawLine(0, w/2, w, w/2);
    painter.drawLine(0, 0, w, w);
    painter.drawLine(0, w, w, 0);

    // draw speakers
    QBrush brush(Qt::darkGray, Qt::SolidPattern);
    painter.setBrush(brush);
    painter.setPen(Qt::darkGray);

    for(int i = 0; i < NUM_SPEAKERS; i++) {
        painter.drawEllipse(m_speakers_coordinates[i] * w, w/50, w/50);
    }

    // draw sources
    brush.setColor(Qt::darkRed);
    painter.setBrush(brush);

    for(int i = 0; i < NUM_SOURCES; i++) {

        painter.drawEllipse(m_sources_coordinates[i], w/25, w/25);
        brush.setColor(Qt::darkGreen);
        painter.setBrush(brush);

        emit sendBackData(QStringLiteral("/touchspat/") + QString::number(i) + "/x",
                          m_sources_coordinates[i].x()/width(), false);
        emit sendBackData(QStringLiteral("/touchspat/") + QString::number(i) + "/y",
                          m_sources_coordinates[i].y()/width(), false);
    }

}

bool TouchSpat::event(QEvent *event) {

    if(active) {

        switch(event->type()) {

        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd: {

            QList<QTouchEvent::TouchPoint> touch_points = static_cast<QTouchEvent*>(event)->touchPoints();

            foreach(const QTouchEvent::TouchPoint &touch_point, touch_points) {

                switch(touch_point.state()) {

                case Qt::TouchPointStationary: continue;
                default: {
                    int selected_source_index = 0;
                    for(int i = 0; i < NUM_SOURCES; i++) {
                        qreal touch_x = touch_point.pos().x(); qreal touch_y = touch_point.pos().y();
                        qreal source_x = m_sources_coordinates[i].x();
                        qreal source_y = m_sources_coordinates[i].y();

                        if(touch_x >= (source_x - TOUCH_AREA_SIZE) && touch_x <= (source_x + TOUCH_AREA_SIZE) &&
                            touch_y >= (source_y - TOUCH_AREA_SIZE) && touch_y <= (source_y + TOUCH_AREA_SIZE)) {
                        selected_source_index = i+1;
                    }
                }
                    if(selected_source_index) {
                    QPointF *source = &m_sources_coordinates[selected_source_index-1];
                    source->setX(touch_point.pos().x());
                    if(source->x() > width()) source->setX(width());
                    else if(source->x() < 0) source->setX(0);
                    source->setY(touch_point.pos().y());
                    if(source->y() > height()) source->setY(height());
                    else if(source->y() < 0) source->setY(0);

                }} break; }} break; }

        default: return QWidget::event(event); }
        return true;
    }
}

void TouchSpat::start() {
    m_polling_timer->start(VIEW_REFRESH_RATE);
    active = true;
}

void TouchSpat::stop() {
    m_polling_timer->stop();
    active = false;
}

QString TouchSpat::getModuleIdentifier() {
    return "TOUCH_SPAT";
}

QList<quarre::QGestureEnum> TouchSpat::getQGestureRequirements() { return EMPTY_QGESTUREREQLIST; }
QList<quarre::QRawSensorDataEnum> TouchSpat::getQRawSensorDataRequirements() {
    return EMPTY_QRAWSENSORREQLIST;
}

QList<QString> TouchSpat::getCustomResponderAddresses() {
    return EMPTY_RESPADDRESSES;
}

void TouchSpat::onReceivedCustomData(QString sender, QList<qreal> values) {}
void TouchSpat::onReceivedGesture(quarre::QGestureEnum gesture) {}
void TouchSpat::onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value) {}
