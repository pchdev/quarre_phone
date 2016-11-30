#ifndef TEXTVIEWER_H
#define TEXTVIEWER_H

#include "interactionmodule.h"
#include "../../_fwd/fwd_enum.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QLabel>
#include <QEvent>
#include <QTouchEvent>

namespace arbre_integral {

class TextViewer : public quarre::InteractionModule {

    Q_OBJECT

public:
    TextViewer();
    ~TextViewer();
    quarre::InteractionModuleEnum getModuleEnumReference();
    void startModule();
    void stopModule();
    QList<quarre::QGestureEnum> getQGestureRequirements();
    QList<quarre::QRawSensorDataEnum> getQRawSensorDataRequirements();
    void onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value);
    void onReceivedGesture(quarre::QGestureEnum gesture);
    void onReceivedMiscData(QString sender, qreal value);
    void updateReadIndex(int index);
    void setTextSize(int size, qreal screen_width);

signals:
    void touchedModuleLeftSide();
    void touchedModuleRightSide();

protected slots:
    void processModuleLeftTouch();
    void processModuleRightTouch();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;

private:
    int m_index;
    QList<QString> m_texts;
    QLabel *m_current_text;

};

}

#endif // TEXTVIEWER_H
