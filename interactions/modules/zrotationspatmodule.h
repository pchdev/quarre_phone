#ifndef ZROTATIONSPATMODULE_H
#define ZROTATIONSPATMODULE_H

#include "interactionmodule.h"

class ZRotationSpatModule : public quarre::InteractionModule {

    Q_OBJECT

public:
    ZRotationSpatModule(quarre::Control *controller, qreal angle_offset = 0);
    ~ZRotationSpatModule();
    quarre::InteractionModuleEnum getModuleEnumReference();
    void startModule();
    void stopModule();
    void onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value);
    void onReceivedGesture(quarre::QGestureEnum gesture);
    QList<quarre::QGestureEnum> getQGestureRequirements();
    QList<quarre::QRawSensorDataEnum> getQRawSensorDataRequirements();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

protected slots:
    //void refreshView();

private:
    qreal m_angle_offset;
    qreal m_azimuth;


};

#endif // ZROTATIONSPATMODULE_H
