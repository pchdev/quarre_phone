#ifndef GESTURE_H
#define GESTURE_H

#include "interactionmodule.h"

namespace arbre_integral {

class WhipGestureViewer : public quarre::InteractionModule {

public:

    WhipGestureViewer();
    ~WhipGestureViewer();
    void startModule();
    void stopModule();
    quarre::InteractionModuleEnum getModuleEnumReference();
    QList<quarre::QGestureEnum> getQGestureRequirements();
    QList<quarre::QRawSensorDataEnum> getQRawSensorDataRequirements();
    void onReceivedGesture(quarre::QGestureEnum gesture);
    void onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value);
    void onReceivedMiscData(QString sender, qreal value);

};

}

#endif // GESTURE_H
