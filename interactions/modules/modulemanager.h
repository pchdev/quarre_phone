#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include "interactionmodule.h"

// add the includes to the modules' headers here
#include "touchspatmodule.h"
#include "zrotationspatmodule.h"

namespace quarre {

class Control;
class InteractionModule;

// add the module ref enum name to the enum in _fwd/fwd_enum.h (this is mandatory)
// and don't forget to push back an instance of the module class in the module manager constructor

class InteractionModuleManager {

public:
    InteractionModuleManager();
    ~InteractionModuleManager();
    QList<quarre::InteractionModule*> getInteractionModulesAccesses() const;
    void setActiveModule(quarre::InteractionModule *module);
    quarre::InteractionModule* getActiveModule() const;

private:
    QList<quarre::InteractionModule*> am_interaction_modules;
    quarre::InteractionModule *r_active_module;

};

}

#endif // MODULEMANAGER_H
