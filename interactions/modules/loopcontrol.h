#ifndef LOOPCONTROL_H
#define LOOPCONTROL_H

#include "interactionmodule.h"
#include "subelements/pad.h"
#include "textviewer.h"

namespace arbre_integral {

class LoopControl : public quarre::InteractionModule {

    Q_OBJECT

public:
    LoopControl(quarre::InteractionModule *viewer);
    ~LoopControl();
    void startModule();
    void stopModule();
    quarre::InteractionModuleEnum getModuleEnumReference();
    QList<quarre::QGestureEnum> getQGestureRequirements();
    QList<quarre::QRawSensorDataEnum> getQRawSensorDataRequirements();
    void onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value);
    void onReceivedGesture(quarre::QGestureEnum gesture);
    void onReceivedMiscData(QString sender, qreal value);

private:
    bool m_loop_started;

};

}

#endif // LOOPCONTROL_H
