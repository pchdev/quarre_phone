#include "modulemanager.h"

using namespace quarre;

InteractionModuleManager::InteractionModuleManager() :
    r_active_module(0) {

    // instantiate modules here by pushing back into the module array, as below
    am_interaction_modules.push_back(new TouchSpatModule(0, 6, 2));
    am_interaction_modules.push_back(new ZRotationSpatModule(0, 0));

}

InteractionModuleManager::~InteractionModuleManager() {
    foreach(quarre::InteractionModule *module, am_interaction_modules) {
        delete module;
    }
}

QList<quarre::InteractionModule*> InteractionModuleManager::getInteractionModulesAccesses() const {
    return am_interaction_modules;
}

void InteractionModuleManager::setActiveModule(InteractionModule *module) {
    r_active_module = module;
}

quarre::InteractionModule* InteractionModuleManager::getActiveModule() const {
    return r_active_module;
}
