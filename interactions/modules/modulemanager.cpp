#include "modulemanager.h"

using namespace quarre;

InteractionModuleManager::InteractionModuleManager() {

    // instantiate modules here,
    // all modules first argument should be a pointer to the main controller


}

InteractionModuleManager::~InteractionModuleManager() {


}

QList<quarre::InteractionModule*> InteractionModuleManager::getInteractionModulesAccesses() const {
    return am_interaction_modules;
}
