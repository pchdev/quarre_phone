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

namespace quarre {

class Control;
class SensorManager : public QObject {

    Q_OBJECT

public:
    SensorManager();
    ~SensorManager();
    void setController(quarre::Control *controller);
    void startGestureRecognition(quarre::QGestureEnum gesture);
    void stopGestureRecognition();

protected slots:
    void onGestureDetection(QString gesture_id);

private:
    quarre::Control *r_control;
    QTimer *m_sensor_timer;
    QCompass *m_compass;
    QCompassReading *m_compass_reader;
    QAccelerometer *m_accelerometer;
    QAccelerometerReading *m_accelerometer_reader;
    QRotationSensor *m_rotation_sensor;
    QRotationReading *m_rotation_reader;
    QSensorGestureManager *m_gesture_manager;
    QSensorGesture *m_sensor_gesture;
    bool poll_x_accel; bool poll_y_accel; bool poll_z_accel;
    bool poll_x_rotation; bool poll_y_rotation; bool poll_z_rotation;
    bool poll_azimuth;
};

}
#endif // SENSORMANAGER_H
