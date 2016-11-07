#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include "../control/control.h"
#include "../_fwd/fwd_enum.h"

#include <QAccelerometerReading>
#include <QRotationReading>
#include <QCompassReading>
#include <QTimer>
#include <QSensorGestureManager>
#include <QSensorGesture>

// should have a separate timer to poll data in order to refresh view ?
// thus control should have a separate callback


namespace quarre {

class Control;
class SensorManager : public QObject {

    Q_OBJECT

public:
    SensorManager();
    ~SensorManager();
    void setController(quarre::Control *controller);
    void setRecognizedGestures(QList<quarre::QGestureEnum> gestures_to_be_recognized);
    void setPolledSensors(QList<quarre::QRawSensorDataEnum> sensors_to_be_polled);
    void voidRecognizedGestures();
    void voidPolledSensors();
    void startGestureRecognition();
    void stopGestureRecognition();
    void startSensorPolling() const;
    void stopSensorPolling() const;
    void setOSCPollingRate();
    void setViewRefreshRate();


protected slots:
    void onGestureDetection(QString gesture_id);
    void onSensorDataPolled();

private:
    QList<quarre::QGestureEnum> am_recognized_gesture;
    QList<quarre::QRawSensorDataEnum> am_sensor_polling;
    quarre::Control *r_control;
    QTimer *m_sensor_timer;
    QTimer *m_view_sensor_timer;
    int m_osc_polling_rate;
    int m_view_refresh_rate;
    QCompass *m_compass;
    QCompassReading *m_compass_reader;
    QAccelerometer *m_accelerometer;
    QAccelerometerReading *m_accelerometer_reader;
    QRotationSensor *m_rotation_sensor;
    QRotationReading *m_rotation_reader;
    QSensorGestureManager *m_gesture_manager;
    QSensorGesture *m_sensor_gesture;
};

}
#endif // SENSORMANAGER_H
