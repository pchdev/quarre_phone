#include "touchspatmodule.h"
#include <QtDebug>

//#define PI_OFFSET M_PI/NUMSPEAKERS
#define VIEW_REFRESH_RATE 30
#define OSC_GRANULARITY 50
#define TOUCH_AREA_SIZE 50

TouchSpatModule::TouchSpatModule(quarre::Control *controller, uint8_t num_speakers, uint8_t num_sources) :
    quarre::InteractionModule(),
    m_num_speakers(num_speakers),
    m_num_sources(num_sources),
    is_active(false),
    m_view_refresh_timer(new QTimer(this)),
    m_osc_polling_timer(new QTimer(this)) {

    this->setController(controller);

    float pi_offset = M_PI/m_num_speakers;

    // COMPUTE SPEAKER POSITIONS
    for(int i = 0; i < m_num_speakers; i++) {
        float to_pi = 2*pi_offset*i + pi_offset;
        m_speaker_x.push_back((sin(to_pi) + 1.f) / 2.f);
        m_speaker_y.push_back((cos(to_pi) + 1.f) / 2.f);
    }

    float w = width();

    // setting up default source positions (to be automated)
    m_sources_x.push_back(w*0.25);
    m_sources_x.push_back(w*0.5);
    m_sources_y.push_back(w*0.5);
    m_sources_y.push_back(w*0.5);

    // setting up refresh timer
    QObject::connect(m_view_refresh_timer, SIGNAL(timeout()), this, SLOT(refreshView()));
    QObject::connect(m_osc_polling_timer, SIGNAL(timeout()), this, SLOT(pollOSC()));

    // misc.
    setAttribute(Qt::WA_AcceptTouchEvents);
}

TouchSpatModule::~TouchSpatModule() {
    if(m_view_refresh_timer->isActive()) m_view_refresh_timer->stop();
    if(m_osc_polling_timer->isActive()) m_osc_polling_timer->stop();
    delete m_view_refresh_timer;
    delete m_osc_polling_timer;
}

void TouchSpatModule::paintEvent(QPaintEvent *event) {

    float w = width();
    QPainter painter(this);

    // draw main ellipse
    QPen pen(Qt::darkGray);
    pen.setWidthF(1.5);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);
    painter.drawEllipse(QPointF(w/2, w/22), w/2, w/2);

    // draw grid lines
    pen.setWidthF(0.6);
    painter.setPen(pen);
    painter.drawLine(w/2, 0, w/2, w);
    painter.drawLine(0, w/2, w/2, w/2);
    painter.drawLine(0, 0, w, w);
    painter.drawLine(0, w, w, 0);

    // draw speakers
    QBrush brush(Qt::darkGray, Qt::SolidPattern);
    painter.setBrush(brush);
    painter.setPen(Qt::darkGray);

    for(int i = 0; i < m_num_speakers; i++) {
        painter.drawEllipse(QPointF(m_speaker_x[i]*w, m_speaker_y[i]*w),
                                    w/50, w/50);
    }

    // draw sources
    brush.setColor(Qt::darkRed);
    painter.setBrush(brush);

    for(int i = 0; i < m_num_sources; i++) {
        painter.drawEllipse(QPointF(m_sources_x[i], m_sources_y[i]), w/25, w/25);
        brush.setColor(Qt::darkGreen);
    }
}

void TouchSpatModule::refreshView() {
    this->update();
}

void TouchSpatModule::pollOSC() {} // tbi

bool TouchSpatModule::event(QEvent *event) {

    if(is_active) {

        switch(event->type()) {

        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd: {

            QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent*>(event)->touchPoints();
            foreach(const QTouchEvent::TouchPoint &touchPoint, touchPoints) {

                switch(touchPoint.state()) {

                case Qt::TouchPointStationary: // don't do anything if this touch points hasn't moved
                continue;

                default: { // else recognize the touched source

                    int selected_source = 0;
                    for(int i= 0; i < m_num_sources; i++) {
                        if((touchPoint.pos().x() >= (m_sources_x[i] - TOUCH_AREA_SIZE) && touchPoint.pos().x() <= (m_sources_x[i] + TOUCH_AREA_SIZE)) &&
                                (touchPoint.pos().y() >= (m_sources_y[i] - TOUCH_AREA_SIZE) && touchPoint.pos().y() <= (m_sources_y[i] + TOUCH_AREA_SIZE))) {
                            selected_source = i+1;
                        }
                    }

                    // horizontal & vertical clipping

                    if(selected_source) {
                        m_sources_x[selected_source-1] = touchPoint.pos().x();
                        if(m_sources_x[selected_source-1] > width()) m_sources_x[selected_source-1] = width();
                        else if(m_sources_x[selected_source-1] < 0) m_sources_x[selected_source-1] = 0;
                        m_sources_y[selected_source -1] = touchPoint.pos().y();
                        if(m_sources_y[selected_source -1] > height()) m_sources_y[selected_source-1] = height();
                        else if(m_sources_y[selected_source -1] < 0) m_sources_y[selected_source -1] = 0;
                    }

                }
                    break;
                }
            }
            break;
        }
        default: // if not a TouchEvent, return the event, else accept the event
            return QWidget::event(event);
        }
        return true;
    }

}

void TouchSpatModule::startModule() { // start polling & refresh timers
    m_view_refresh_timer->start(VIEW_REFRESH_RATE);
    m_osc_polling_timer->start(OSC_GRANULARITY);
    is_active = true;
}

void TouchSpatModule::stopModule() {
    m_view_refresh_timer->stop();
    m_osc_polling_timer->stop();
    is_active = false;
}

quarre::InteractionModuleEnum TouchSpatModule::getModuleEnumReference() {
    return quarre::TouchSpat;
}

// no sensor data | gesture required
QList<quarre::QGestureEnum> TouchSpatModule::getQGestureRequirements() {return NULL;}
QList<quarre::QRawSensorDataEnum> TouchSpatModule::getQRawSensorDataRequirements() {return NULL;}

// these should return errors, as no data is required
void TouchSpatModule::onReceivedGesture(quarre::QGestureEnum gesture) {}
void TouchSpatModule::onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value) {}
