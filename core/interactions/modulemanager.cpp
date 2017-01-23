#include "modulemanager.h"
#include <QtDebug>

using namespace quarre;

InteractionModuleManager::InteractionModuleManager() :
    r_active_module(nullptr) {

    QPluginLoader test_loader("libquarre_plugin_test.1.0.0");
    if(!test_loader.load()) qDebug() << "FAILED TO LOAD TEST PLUGIN";
    else qDebug() << "PLUGIN SUCCESFULLY LOADED!";

}

InteractionModuleManager::~InteractionModuleManager() {
    foreach(quarre::InteractionModule *module, am_interaction_modules) {
        delete module;}
}

QList<quarre::InteractionModule*> InteractionModuleManager::getInteractionModulesReferences() const {
    return am_interaction_modules;
}

void InteractionModuleManager::setActiveModule(InteractionModule *module) {
    r_active_module = module;
}

quarre::InteractionModule* InteractionModuleManager::getActiveModule() const {
    return r_active_module;
}
