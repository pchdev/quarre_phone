#ifndef COUNTDOWNWIDGET_H
#define COUNTDOWNWIDGET_H

#include "../control/control.h"
#include <QTimer>
#include <QWidget>
#include <QPainter>
#include <QEvent>
#include <math.h>

namespace quarre {

class CountdownWidget : public QWidget {

    Q_OBJECT

public:
    CountdownWidget(qreal font_ratio = 1);
    void triggerTimer(int length_in_seconds);
    void stopTimer();
    ~CountdownWidget();
    void setControl(quarre::Control *control);

protected slots:
    void updateTick();
signals:
    void timeOver();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    bool event(QEvent *event) Q_DECL_OVERRIDE;

private:
    qreal m_font_ratio;
    quarre::Control *r_control;
    QTimer *m_timer;
    long m_timer_end_point;
    bool m_timer_is_inf;
    long m_current_tick;
    int m_time_left_to_display;
    float m_timer_phase;
};

}

#endif // COUNTDOWNWIDGET_H
