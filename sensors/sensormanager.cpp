#include "sensormanager.h"
#include <QDebug>

#define GRANULARITY 30

using namespace quarre;

SensorManager::SensorManager() :
    poll_x_accel(false),
    poll_y_accel(false),
    poll_z_accel(false),
    poll_x_rotation(false),
    poll_y_rotation(false),
    poll_z_rotation(false),
    m_accelerometer(new QAccelerometer()),
    m_compass(new QCompass()),
    m_rotation_sensor(new QRotationSensor()),
    m_gesture_manager(new QSensorGestureManager()),
    m_sensor_timer(new QTimer(this)) {

    qDebug() << "getting gesture IDs...";

    foreach(const QString &gesture, m_gesture_manager->gestureIds()) {
        QStringList recognizer_signals = m_gesture_manager->recognizerSignals(gesture);
        qDebug() << gesture;
    }

}

SensorManager::~SensorManager() {

    delete m_rotation_reader;
    delete m_rotation_sensor;
    delete m_accelerometer_reader;
    delete m_accelerometer;
    delete m_compass_reader;
    delete m_compass;
    delete m_sensor_timer;
    delete m_sensor_gesture;
    delete m_gesture_manager;

}

void SensorManager::setController(quarre::Control *control) {
    r_control = control;
}

void SensorManager::onGestureDetection(QString gesture_id) {
    qDebug() << gesture_id << " detected!";
    for(int i = 0; i < quarre::QGESTURE_ENUMSIZE; i++) {
        if(gesture_id == quarre::qgesture_names[i]) {
            gesture_id = "/gesture/" + gesture_id;

        }

    }

}

void SensorManager::startGestureRecognition(quarre::QGestureEnum gesture) {

    QString recognizer = quarre::qgesture_names[gesture];
    QStringList recognizers_list = m_gesture_manager->gestureIds();

    m_sensor_gesture = new QSensorGesture(QStringList() << recognizer, this);
    m_sensor_gesture->startDetection();
    QObject::connect(m_sensor_gesture, SIGNAL(deteted(QString)), this, SLOT(onGestureDetection(QString)));

}

void SensorManager::stopGestureRecognition() {
    QObject::disconnect(m_sensor_gesture, SIGNAL(detected(QString)), this, SLOT(onGestureDetection(QString)));
    m_sensor_gesture->stopDetection();
    delete m_sensor_gesture;
}






