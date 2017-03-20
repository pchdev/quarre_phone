#include "sensormanager.h"
#include <QDebug>

#define GRANULARITY 30

using namespace quarre;

SensorManager::SensorManager() :
    m_accelerometer(new QAccelerometer()),
    m_compass(new QCompass()),
    m_rotation_sensor(new QRotationSensor()),
    m_gesture_manager(new QSensorGestureManager()) {

    foreach(const QString &gesture, m_gesture_manager->gestureIds()) {
        QStringList recognizer_signals = m_gesture_manager->recognizerSignals(gesture);
        qDebug() << gesture; }

    QObject::connect(m_accelerometer, SIGNAL(readingChanged()), this, SLOT(accelerometerReading()));
    QObject::connect(m_compass, SIGNAL(readingChanged()), this, SLOT(compassReading()));
    QObject::connect(m_rotation_sensor, SIGNAL(readingChanged()), this, SLOT(rotationReading()));

    qDebug() << "data rates available: " << m_accelerometer->availableDataRates();

}

SensorManager::~SensorManager() {}
void SensorManager::setController(quarre::Control *control) {r_control = control;}


// SENSORS ------------------------------------------------------------

void SensorManager::setPolledSensors(QList<QRawSensorDataEnum> sensors_to_be_polled) {
    am_sensor_polling = sensors_to_be_polled;
}

void SensorManager::startSensorPolling() {

    if(!am_sensor_polling.isEmpty()) {

        foreach(quarre::QRawSensorDataEnum sensor, am_sensor_polling) {

            switch(sensor) {
            case quarre::Accelerometer_x:
                m_accelerometer->start(); break;
            case quarre::Accelerometer_y:
                m_accelerometer->start(); break;
            case quarre::Accelerometer_z:
                m_accelerometer->start(); break;
            case quarre::Azimuth:
                m_compass->start(); break;
            case quarre::Rotation_x:
                m_rotation_sensor->start(); break;
            case quarre::Rotation_y:
                m_rotation_sensor->start(); break;
            case quarre::Rotation_z:
                m_rotation_sensor->start(); break;
            }
        }
    }
}

void SensorManager::accelerometerReading() {

    qreal value;

    foreach(quarre::QRawSensorDataEnum sensor, am_sensor_polling) {
        switch(sensor) {
        case quarre::Accelerometer_x:
            value = m_accelerometer->reading()->x(); break;
        case quarre::Accelerometer_y:
            value = m_accelerometer->reading()->y(); break;
        case quarre::Accelerometer_z:
            value = m_accelerometer->reading()->z(); break;
        }

        r_control->processSensorCallback(sensor, value);
    }
}


void SensorManager::compassReading() {

    qreal value;

    foreach(quarre::QRawSensorDataEnum sensor, am_sensor_polling) {
        if(sensor == quarre::Azimuth) value = m_compass->reading()->azimuth();
        r_control->processSensorCallback(sensor, value);
    }

}

void SensorManager::rotationReading() {

    qreal value;

    foreach(quarre::QRawSensorDataEnum sensor, am_sensor_polling) {

        switch(sensor) {

        case quarre::Rotation_x:
            value = m_rotation_sensor->reading()->x(); break;
        case quarre::Rotation_y:
            value = m_rotation_sensor->reading()->y(); break;
        case quarre::Rotation_z:
            value = m_rotation_sensor->reading()->z(); break;
        }

        r_control->processSensorCallback(sensor, value);
    }
}


void SensorManager::voidPolledSensors() { am_sensor_polling.clear(); }
void SensorManager::stopSensorPolling() {
    m_accelerometer->stop();
    m_compass->stop();
    m_rotation_sensor->stop();
}

// GESTURES ------------------------------------------------------------

// convert enum to qstrings
void SensorManager::setRecognizedGestures(QList<QGestureEnum> gestures_to_be_recognized) {
    foreach(quarre::QGestureEnum gesture, gestures_to_be_recognized) {
        QString recognizer = "QtSensors." + quarre::qgesture_names[gesture];
        am_gesture_recognizers << recognizer; }
    qDebug() << am_gesture_recognizers; }

// unfortunately, qsensorgesture has to be rebuilt when recognizers id list changes
void SensorManager::startGestureRecognition() {
    m_sensor_gesture = new QSensorGesture(am_gesture_recognizers, this);
    m_sensor_gesture->startDetection();
    QObject::connect(m_sensor_gesture, SIGNAL(detected(QString)),
                     this, SLOT(onGestureDetection(QString))); }

void SensorManager::onGestureDetection(QString gesture_id) {

    qDebug() << gesture_id << " detected!";

    if(gesture_id == "twistLeft" || gesture_id == "twistRight") {
        gesture_id = "twist";
    }

    for(int i = 0; i < quarre::QGESTURE_ENUMSIZE; i++) {
        if(gesture_id == quarre::qgesture_names[i])
            r_control->processGestureCallback(static_cast<quarre::QGestureEnum>(i), 1); }}

void SensorManager::stopGestureRecognition() {
    QObject::disconnect(m_sensor_gesture, SIGNAL(detected(QString)), this, SLOT(onGestureDetection(QString)));
    m_sensor_gesture->stopDetection();
    delete m_sensor_gesture; }

void SensorManager::voidRecognizedGestures() { am_gesture_recognizers.clear(); }
