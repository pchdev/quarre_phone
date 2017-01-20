#ifndef FWD_ENUM_H
#define FWD_ENUM_H

#include <QString>
#include <QList>
#include <QtGlobal>

namespace quarre {

// QGESTURE
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

// RAW SENSOR DATA
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
    "compass/azimuth",
    "rotation/x",
    "rotation/y",
    "rotation/z"
};

}

#endif // FWD_ENUM_H
