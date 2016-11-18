#include "textviewer.h"

using namespace arbre_integral;

TextViewer::TextViewer() {

}

TextViewer::~TextViewer() {}
quarre::InteractionModuleEnum TextViewer::getModuleEnumReference() { return quarre::AI_TEXTVIEWER; }
void TextViewer::startModule() {}
void TextViewer::stopModule() {}
QList<quarre::QGestureEnum> TextViewer::getQGestureRequirements() {}
QList<quarre::QRawSensorDataEnum> TextViewer::getQRawSensorDataRequirements() {}
void TextViewer::onReceivedGesture(quarre::QGestureEnum gesture) {}
void TextViewer::onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value) {}

