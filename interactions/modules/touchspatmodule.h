#ifndef TOUCHSPATMODULE_H
#define TOUCHSPATMODULE_H

#include "interactionmodule.h"

#include <QTimer>
#include <QEvent>
#include <QTouchEvent>
#include <math.h>
#include <vector>

class TouchSpatModule : public quarre::InteractionModule {

    Q_OBJECT

public:
    TouchSpatModule(quarre::Control *controller, uint8_t num_speakers = 6, uint8_t num_sources = 2);
    ~TouchSpatModule();
    quarre::InteractionModuleEnum getModuleEnumReference();
    void startModule();
    void stopModule();
    void onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value);
    void onReceivedGesture(quarre::QGestureEnum gesture);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    bool event(QEvent *event) Q_DECL_OVERRIDE;

protected slots:
    void refreshView();
    void pollOSC();

private:
    QTimer *m_view_refresh_timer;
    QTimer *m_osc_polling_timer;
    uint8_t m_num_sources;
    uint8_t m_num_speakers;
    std::vector<float> m_sources_x;
    std::vector<float> m_sources_y;
    std::vector<float> m_speaker_x;
    std::vector<float> m_speaker_y;
    bool is_active;
};

#endif // TOUCHSPATMODULE_H
