#ifndef ROTATIONSPAT_H
#define ROTATIONSPAT_H

#include "rotationspat_global.h"
#include "../quarreplugininterface.h"
#include <QPainter>

class ROTATIONSPATSHARED_EXPORT RotationSpat final :
    public quarre::InteractionModule {

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org quarre.module.NATIVE.RotationSpat")
    Q_INTERFACES(quarre::InteractionModule)


public:

    RotationSpat();
    ~RotationSpat();
    void start() override;
    void stop() override;
    QString getModuleIdentifier() override;
    QList<quarre::QGestureEnum> getQGestureRequirements() override;
    QList<quarre::QRawSensorDataEnum> getQRawSensorDataRequirements() override;
    QList<QString> getCustomResponderAddresses() override;
    void onReceivedCustomData(QString sender, QList<qreal> values) override;
    void onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value) override;
    void onReceivedGesture(quarre::QGestureEnum gesture) override;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    qreal m_azimuth;


};

#endif // ROTATIONSPAT_H
