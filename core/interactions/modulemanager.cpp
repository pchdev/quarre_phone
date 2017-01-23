#include "modulemanager.h"

// add the includes to the modules' headers here

using namespace quarre;

InteractionModuleManager::InteractionModuleManager() :
    r_active_module(nullptr) {
}

InteractionModuleManager::~InteractionModuleManager() {
    foreach(quarre::InteractionModule *module, am_interaction_modules) {
        delete module;}}

QList<quarre::InteractionModule*> InteractionModuleManager::getInteractionModulesAccesses() const {
    return am_interaction_modules;}

void InteractionModuleManager::setActiveModule(InteractionModule *module) {
    r_active_module = module;}

quarre::InteractionModule* InteractionModuleManager::getActiveModule() const {
    return r_active_module;}
