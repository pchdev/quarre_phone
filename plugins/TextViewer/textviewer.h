#ifndef TEXTVIEWER_H
#define TEXTVIEWER_H

#include "textviewer_global.h"
#include "../quarreplugininterface.h"
#include <QtPlugin>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QLabel>
#include <QEvent>
#include <QTouchEvent>
#include <QWidget>

class TEXTVIEWERSHARED_EXPORT TextViewer :
        public quarre::InteractionModule {

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.quarre.module.AI.TextViewer")
    Q_INTERFACES(quarre::InteractionModule)

public:
    TextViewer();
    ~TextViewer();
    void start();
    void stop();
    QString getModuleIdentifier();
    QList<quarre::QGestureEnum> getQGestureRequirements();
    QList<quarre::QRawSensorDataEnum> getQRawSensorDataRequirements();
    QList<QString> getCustomResponderAddresses();
    void onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value);
    void onReceivedGesture(quarre::QGestureEnum gesture);
    void onReceivedCustomData(QString sender, QList<qreal> values);

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;

private:
    void processModuleLeftTouch();
    void processModuleRightTouch();
    int m_index;
    QList<QString> m_texts;
    QLabel *m_current_text;

};

#endif // TEXTVIEWER_H
