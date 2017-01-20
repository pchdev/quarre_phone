#ifndef INTERACTIONMODULE_H
#define INTERACTIONMODULE_H

#include "../../control/control.h"
#include "../../_fwd/fwd_enum.h"

namespace quarre {

class Control;
class InteractionModule : public QWidget {

    Q_OBJECT

public:
    InteractionModule();
    virtual ~InteractionModule();
    virtual quarre::InteractionModuleEnum getModuleEnumReference() = 0;
    virtual void startModule() = 0;
    virtual void stopModule() = 0;
    virtual QList<quarre::QGestureEnum> getQGestureRequirements() = 0;
    virtual QList<quarre::QRawSensorDataEnum> getQRawSensorDataRequirements() = 0;
    virtual void onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value) = 0;
    virtual void onReceivedGesture(quarre::QGestureEnum gesture) = 0;
    virtual void onReceivedMiscData(QString sender, qreal value) = 0;
};

}

#endif // INTERACTIONMODULE_H
