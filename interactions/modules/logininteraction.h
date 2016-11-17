#ifndef LOGININTERACTION_H
#define LOGININTERACTION_H

#include "interactionmodule.h"
#include "../../_fwd/fwd_enum.h"

namespace arbre_integral {

class LoginInteraction : public quarre::InteractionModule {

    Q_OBJECT

public:
    LoginInteraction();
    ~LoginInteraction();
    void startModule();
    void stopModule();
    quarre::InteractionModuleEnum getModuleEnumReference();
    QList<quarre::QGestureEnum> getQGestureRequirements();
    QList<quarre::QRawSensorDataEnum> getQRawSensorDataRequirements();
    void onReceivedGesture(quarre::QGestureEnum gesture);
    void onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    bool event(QEvent *event) Q_DECL_OVERRIDE;

private:
    bool is_active;
};

}

#endif // LOGININTERACTION_H
