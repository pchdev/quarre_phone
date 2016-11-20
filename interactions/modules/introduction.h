#ifndef INTRODUCTION_H
#define INTRODUCTION_H

#include "interactionmodule.h"
#include "../../_fwd/fwd_enum.h"

namespace arbre_integral {

class Introduction : public quarre::InteractionModule {

    Q_OBJECT

public:
    Introduction();
    ~Introduction();
    void startModule();
    void stopModule();
    quarre::InteractionModuleEnum getModuleEnumReference();
    QList<quarre::QGestureEnum> getQGestureRequirements();
    QList<quarre::QRawSensorDataEnum> getQRawSensorDataRequirements();
    void onReceivedGesture(quarre::QGestureEnum gesture);
    void onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value);

};

}

#endif // INTRODUCTION_H
