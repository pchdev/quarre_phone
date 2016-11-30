#include "modulemanager.h"

// add the includes to the modules' headers here
#include "touchspatmodule.h"
#include "zrotationspatmodule.h"
#include "logininteraction.h"
#include "textviewer.h"
#include "introduction.h"
#include "nullmodule.h"
#include "gesture.h"
#include "loopcontrol.h"

using namespace quarre;

InteractionModuleManager::InteractionModuleManager() :
    r_active_module(nullptr) {

    // instantiate modules here by pushing back into the module array, as below

    quarre::InteractionModule *text_viewer = new arbre_integral::TextViewer;

    am_interaction_modules.push_back(new arbre_integral::NullModule);
    am_interaction_modules.push_back(new arbre_integral::Introduction);
    am_interaction_modules.push_back(new arbre_integral::LoginInteraction);
    am_interaction_modules.push_back(text_viewer);
    am_interaction_modules.push_back(new arbre_integral::WhipGestureViewer);
    am_interaction_modules.push_back(new arbre_integral::LoopControl(text_viewer));

    //am_interaction_modules.push_back(new TouchSpatModule(0, 6, 2));
    //am_interaction_modules.push_back(new ZRotationSpatModule(0, 0));
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
