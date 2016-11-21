#include "countdownwidget.h"

#define REFRESH_RATE 25

using namespace quarre;
CountdownWidget::CountdownWidget(qreal font_ratio) :
    m_font_ratio(font_ratio),
    m_timer_end_point(0),
    m_current_tick(0),
    m_time_left_to_display(0),
    m_timer_phase(0.f),
    m_timer_is_inf(false),
    m_timer(new QTimer(this)) {
QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTick()));}
CountdownWidget::~CountdownWidget() {delete m_timer;}

void CountdownWidget::paintEvent(QPaintEvent *event) {

    float r = width()/2.f;
    float phase = -(m_timer_phase*360.f);

    QPainter painter(this);
    QPen pen(Qt::darkGray);

    pen.setWidthF(width()*0.005);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);

    // draw double ellipse
    painter.drawEllipse(QPointF(r,r), r, r);
    painter.drawEllipse(QPointF(r,r), r*0.95, r*0.95);

    // draw counting arc path
    QRectF rect(0, 0, width(), height());
    QPainterPath path;
    path.moveTo(QPoint(r,r));
    path.arcTo(rect, 90, phase);

    QBrush brush(Qt::darkGray, Qt::SolidPattern);

    // if <= 5s left, draw the arc in red, text in white
    if(m_time_left_to_display <= 5 && m_time_left_to_display != 0 && m_timer_phase >= 0.75) {
        brush.setColor(Qt::darkRed);
        pen.setColor(Qt::white);
    } else { pen.setColor(Qt::black);}

    painter.fillPath(path, brush);
    painter.setFont(QFont("Arial", 40*m_font_ratio, 2));
    painter.setPen(pen);

    // in case of undefined length
    QString display;
    if(m_timer_is_inf) display = "inf";
    else display = QString::number(m_time_left_to_display);

    painter.drawText(QRect(0, 0, r*2, r*2), display, QTextOption(Qt::AlignCenter));

}

void CountdownWidget::triggerTimer(int length_in_seconds) {
    m_timer->start(REFRESH_RATE);
    m_timer_end_point = 1000;
    m_time_left_to_display = length_in_seconds;
    if(!length_in_seconds) m_timer_is_inf = true;
    else m_timer_is_inf = false;
    m_current_tick = 0;}

void CountdownWidget::stopTimer() {
    m_timer_end_point = 0;
    m_timer->stop();
    m_time_left_to_display = 0;
    m_timer_phase = 0.f;
    this->update();}

void CountdownWidget::updateTick() {
    m_current_tick += REFRESH_RATE;
    if(m_current_tick >= m_timer_end_point) m_current_tick -= m_timer_end_point;
    if(m_current_tick == 0) m_time_left_to_display -= 1;
    if(m_time_left_to_display == 0 && !m_timer_is_inf) {
        this->stopTimer();
        emit timeOver();}
    m_timer_phase = (float) m_current_tick/m_timer_end_point;
    this->update();
}
