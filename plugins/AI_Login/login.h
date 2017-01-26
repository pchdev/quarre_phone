#ifndef LOGIN_H
#define LOGIN_H

#include "ai_login_global.h"
#include "../quarreplugininterface.h"

class AI_LOGINSHARED_EXPORT Login :
    public quarre::InteractionModule {

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.quarre.module.AI.LOGIN")
    Q_INTERFACES(quarre::InteractionModule)

public:

    Login();
    ~Login();
    void start();
    void stop();
    QString getModuleIdentifier();
    QList<quarre::QGestureEnum> getQGestureRequirements();
    QList<quarre::QRawSensorDataEnum> getQRawSensorDataRequirements();
    QList<QString> getCustomResponderAddresses();
    void onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value);
    void onReceivedGesture(quarre::QGestureEnum gesture);
    void onReceivedCustomData(QString sender, QList<qreal> values);
};

#endif // LOGIN_H
