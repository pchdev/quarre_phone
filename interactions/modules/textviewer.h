#ifndef TEXTVIEWER_H
#define TEXTVIEWER_H

#include "interactionmodule.h"
#include "../../_fwd/fwd_enum.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

namespace arbre_integral {

class TextViewer : public quarre::InteractionModule {

public:

    TextViewer();
    ~TextViewer();
    quarre::InteractionModuleEnum getModuleEnumReference() = 0;
    void startModule() = 0;
    void stopModule() = 0;
    QList<quarre::QGestureEnum> getQGestureRequirements() = 0;
    QList<quarre::QRawSensorDataEnum> getQRawSensorDataRequirements() = 0;
    void onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value) = 0;
    void onReceivedGesture(quarre::QGestureEnum gesture) = 0;

private:
    QList<QJsonArray> m_cernes;

};

}

#endif // TEXTVIEWER_H
