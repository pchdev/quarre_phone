#ifndef FWD_ENUM_H
#define FWD_ENUM_H

#include <QString>
#include <QList>

namespace quarre {

// MODULES

typedef enum {
    None,
    Introduction,
    TouchSpat,
    Z_Rotation_spat,
    Pads,
    Slider,
    WhipGesture,
    CoverGesture,
    MODULE_ENUMSIZE
} InteractionModuleEnum;

static const QList<QString> module_names = {
    "None",
    "Introduction",
    "TouchSpat",
    "Z_Rotation_spat",
    "Pads",
    "Slider",
    "WhipGesture",
    "CoverGesture"
};


static_assert(module_names.length() == MODULE_ENUMSIZE,
              "Module Enum's size doesn't match its QString translation");

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

static_assert(qgesture_names.length() == QGESTURE_ENUMSIZE,
              "QGesture Enum's size doesn't match its QString translation");


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
    "accelerometers_z",
    "compass/azimuth",
    "rotation/x",
    "rotation/y",
    "rotation/z"
};

static_assert(qrawsensor_names.length() == QRAWSENSORDATA_ENUMSIZE,
              "QRawSensorData Enum's size doesn't match its QString translation");

}

#endif // FWD_ENUM_H
