#ifndef QUARREPLUGININTERFACE_H
#define QUARREPLUGININTERFACE_H

#include <QString>
#include <QList>
#include <QWidget>

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
} QRawSensorDataEnum;

static const QList<QString> qrawsensor_names = {
    "accelerometers/x",
    "accelerometers/y",
    "accelerometers/z",
    "azimuth",
    "rotation/x",
    "rotation/y",
    "rotation/z"
};

#define EMPTY_QRAWSENSORREQLIST QList<quarre::QRawSensorDataEnum>()
#define EMPTY_QGESTUREREQLIST QList<quarre::QGestureEnum>()
#define EMPTY_RESPADDRESSES Qlist<QString>()

class InteractionModule : public QWidget {

    Q_OBJECT

public:
    virtual ~InteractionModule();
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual QString getModuleIdentifier() = 0;
    virtual QList<quarre::QGestureEnum> getQGestureRequirements() = 0;
    virtual QList<quarre::QRawSensorDataEnum>getQRawSensorDataRequirements() = 0;
    virtual QList<QString> getCustomResponderAddresses() = 0;
    virtual void onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value) =0;
    virtual void onReceivedGesture(quarre::QGestureEnum gesture) = 0;
    virtual void onReceivedCustomData(QString sender, QList<qreal> values) = 0;

signals:
    void sendBackData(QString address, qreal value, bool vibrate);
};

}


#endif // QUARREPLUGININTERFACE_H
