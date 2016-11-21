#include "interactionmodule.h"

using namespace quarre;

InteractionModule::InteractionModule() {}
InteractionModule::~InteractionModule() {}
void InteractionModule::setController(quarre::Control *control) {r_control = control;}
void InteractionModule::onReceivedMiscData(QString sender, qreal value) {}


