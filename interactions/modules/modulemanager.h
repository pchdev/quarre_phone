#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include "interactionmodule.h"
#include "../../control/control.h"

// add the includes to the modules' headers here

namespace quarre {

class Control;
class InteractionModule;

// add the module ref enum name to the enum in _fwd/fwd_enum.h (this is mandatory)
// and don't forget to push back an instance of the module class in the module manager constructor

class InteractionModuleManager {

public:
    InteractionModuleManager();
    ~InteractionModuleManager();
    void setController(quarre::Control *controller);
    QList<quarre::InteractionModule*> getInteractionModulesAccesses() const;

private:
    QList<quarre::InteractionModule*> am_interaction_modules;

};

}

#endif // MODULEMANAGER_H
