#include "sensormanager.h"
#include <QDebug>

#define GRANULARITY 30

using namespace quarre;

SensorManager::SensorManager() :
    m_accelerometer(new QAccelerometer()),
    m_compass(new QCompass()),
    m_rotation_sensor(new QRotationSensor()),
    m_gesture_manager(new QSensorGestureManager()),
    m_osc_polling_rate(50),
    m_sensor_timer(new QTimer(this)) {

    qDebug() << "getting gesture IDs...";

    foreach(const QString &gesture, m_gesture_manager->gestureIds()) {
        QStringList recognizer_signals = m_gesture_manager->recognizerSignals(gesture);
        qDebug() << gesture; }}

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

void SensorManager::setController(quarre::Control *control) {r_control = control;}

// SENSOR POLLING

void SensorManager::setPolledSensors(QList<QRawSensorDataEnum> sensors_to_be_polled) {
    am_sensor_polling = sensors_to_be_polled; }

void SensorManager::startSensorPolling() const {
    m_sensor_timer->start(GRANULARITY); }

void SensorManager::onSensorDataPolled() {

    foreach(quarre::QRawSensorDataEnum sensor, am_sensor_polling) {

        qreal value;

        switch(sensor) {
        case quarre::Accelerometer_x:
            value = m_accelerometer_reader->x();
            break;
        case quarre::Accelerometer_y:
            value = m_accelerometer_reader->y();
            break;
        case quarre::Accelerometer_z:
            value = m_accelerometer_reader->z();
            break;
        case quarre::Azimuth:
            value = m_compass_reader->azimuth();
            break;
        case quarre::Rotation_x:
            value = m_rotation_reader->x();
            break;
        case quarre::Rotation_y:
            value = m_rotation_reader->y();
            break;
        case quarre::Rotation_z:
            value = m_rotation_reader->z();
            break;
        }

        r_control->processSensorCallback(sensor, value);
    }
}

void SensorManager::voidPolledSensors() { am_sensor_polling.clear(); }
void SensorManager::stopSensorPolling() const { m_sensor_timer->stop(); }

// GESTURE RECOGNITION

// convert enum to qstrings
void SensorManager::setRecognizedGestures(QList<QGestureEnum> gestures_to_be_recognized) {

    qDebug() << gestures_to_be_recognized;

    foreach(quarre::QGestureEnum gesture, gestures_to_be_recognized) {
        QString recognizer = "QtSensors." + quarre::qgesture_names[gesture];
        qDebug() << "recognizer added: " << recognizer;
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
    for(int i = 0; i < quarre::QGESTURE_ENUMSIZE; i++) {
        if(gesture_id == quarre::qgesture_names[i])
            r_control->processGestureCallback(static_cast<quarre::QGestureEnum>(i), 1); }}

void SensorManager::stopGestureRecognition() {
    QObject::disconnect(m_sensor_gesture, SIGNAL(detected(QString)), this, SLOT(onGestureDetection(QString)));
    m_sensor_gesture->stopDetection();
    delete m_sensor_gesture; }

void SensorManager::voidRecognizedGestures() { am_gesture_recognizers.clear(); }
