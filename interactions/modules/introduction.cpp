#include "introduction.h"

#include <QLayout>
#include <QLabel>
#include <QPushButton>

using namespace arbre_integral;

Introduction::Introduction(){
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *intro_title = new QLabel("ARBRE INTEGRAL");
    QFont play_font("Arial", 20);
    QPushButton *play_button = new QPushButton("SYNCHRONISATION - NOIR");
    play_button->setFont(play_font);
    layout->addWidget(intro_title, 0, Qt::AlignCenter);
    layout->addWidget(play_button, 0, Qt::AlignCenter);
    QObject::connect(play_button, SIGNAL(pressed()), this, SLOT(onPlayButtonPressed()));}

Introduction::~Introduction() {}
quarre::InteractionModuleEnum Introduction::getModuleEnumReference() { return quarre::AI_INTRODUCTION; }
void Introduction::startModule() {}
void Introduction::stopModule() {}
QList<quarre::QGestureEnum> Introduction::getQGestureRequirements() {}
QList<quarre::QRawSensorDataEnum> Introduction::getQRawSensorDataRequirements() {}
void Introduction::onReceivedGesture(quarre::QGestureEnum gesture) {}
void Introduction::onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value) {}
void Introduction::onReceivedMiscData(QString sender, qreal value) {}

void Introduction::onPlayButtonPressed() {
    r_control->processModuleCallback("/playbutton", 1, true);}


