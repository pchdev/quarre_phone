#include "interactionmodule.h"

using namespace quarre;

InteractionModule::InteractionModule() :
    am_qgesture_requirements(new QList),
    am_qraw_sensor_data_requirements(new QList) {}

InteractionModule::~InteractionModule() {}

void InteractionModule::setController(quarre::Control *control) {
    r_control = control;
}


