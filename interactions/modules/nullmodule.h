#ifndef NULLMODULE_H
#define NULLMODULE_H

#include "interactionmodule.h"
#include "../../_fwd/fwd_enum.h"

namespace arbre_integral {

class NullModule : public quarre::InteractionModule {

    Q_OBJECT

public:
    NullModule();
    ~NullModule();
    void startModule();
    void stopModule();
    quarre::InteractionModuleEnum getModuleEnumReference();
    QList<quarre::QGestureEnum> getQGestureRequirements();
    QList<quarre::QRawSensorDataEnum> getQRawSensorDataRequirements();
    void onReceivedGesture(quarre::QGestureEnum gesture);
    void onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value);
};

}

#endif // NULLMODULE_H
