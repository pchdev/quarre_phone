#ifndef FWD_ENUM_H
#define FWD_ENUM_H

namespace quarre {

typedef enum {
    None,
    Introduction,
    TouchSpat,
    Z_Rotation_spat,
    Pads,
    Slider,
    WhipGesture,
    CoverGesture
} InteractionModuleEnum;

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

// allows const char* bindings

static const char* qgesture_names[] = {
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

static_assert(sizeof(quarre::qgesture_names)/sizeof(char*) == quarre::QGESTURE_ENUMSIZE,
                     "quarre gestures : enum size don't match");

typedef enum {
    Accelerometer_x,
    Accelerometer_y,
    Accelerometer_z,
    Azimuth,
    Rotation_x,
    Rotation_y,
    Rotation_z
} QRawSensorDataEnum;

}

#endif // FWD_ENUM_H
