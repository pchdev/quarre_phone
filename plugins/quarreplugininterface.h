#ifndef QUARREPLUGININTERFACE_H
#define QUARREPLUGININTERFACE_H

#include <QString>
#include <QList>
#include <QtGlobal>

namespace quarre {

typedef enum {
    Cover,
    DoubleTap,
    Hover,
    Freefall,
    Pickup,
    Shake,
    Shake2,
    Slam,
    Turnover,
    Twist,
    Whip,
    QGESTURE_ENUMSIZE
} QGestureEnum;

static const QList<QString> qgesture_names = {
    "cover",
    "doubletap",
    "hover",
    "landed",
    "pickup",
    "shake",
    "shake2",
    "slam",
    "turnover",
    "twist",
    "whip"
};

typedef enum {
    Accelerometer_x,
    Accelerometer_y,
    Accelerometer_z,
    Azimuth,
    Rotation_x,
    Rotation_y,
    Rotation_z,
    QRAWSENSORDATA_ENUMSIZE
} QrawSensorDataEnum;

class Control : public QObject {

public:
    void processModuleCallback(QString address, qreal value, bool vibrate) const;
    void processModuleCallback(QString address, bool vibrate) const;
};

class InteractionModule {

public:
    virtual ~InteractionModule();
    virtual QString getModuleIdentifier() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual QList<quarre::QGestureEnum> getQGestureRequirements() = 0;
    virtual QList<quarre::QRawSensorData>getQRawSensorDataRequirements() = 0;
    virtual QList<QString> getCustomResponderAddresses() = 0;
    virtual void onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value) =0;
    virtual void onReceivedGesture(quarre::QGestureEnum gesture) = 0;
    virtual void onReceivedCustomData(QString sender, qreal value) = 0;
    virtual void setController(quarre::Control *control);
};

}


#endif // QUARREPLUGININTERFACE_H
