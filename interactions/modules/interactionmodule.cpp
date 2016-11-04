#include "interactionmodule.h"

using namespace quarre;

InteractionModule::InteractionModule() {
   // num_instantiated_modules++;
}

InteractionModule::~InteractionModule() {
    //num_instantiated_modules--;
}

void InteractionModule::setController(quarre::Control *control) {
    r_control = control;
}


