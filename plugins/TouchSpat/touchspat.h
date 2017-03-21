#ifndef TOUCHSPAT_H
#define TOUCHSPAT_H

#include "touchspat_global.h"
#include "../quarreplugininterface.h"
#include <QPainter>
#include <QTouchEvent>
#include <QTimer>

class TOUCHSPATSHARED_EXPORT TouchSpat final :
    public quarre::InteractionModule {

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.quarre.module.NATIVE.TouchSpat")
    Q_INTERFACES(quarre::InteractionModule)

public:

    TouchSpat();
    ~TouchSpat();
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
    bool event(QEvent *event) Q_DECL_OVERRIDE;

private:
    bool active;
    void initSpeakerPositions();
    void initSourcesPositions();
    QTimer *m_polling_timer;
    QList<QPointF> m_sources_coordinates;
    QList<QPointF> m_speakers_coordinates;


};

#endif // TOUCHSPAT_H
