#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include "../../plugins/quarreplugininterface.h"

namespace quarre {

class Control;
class InteractionModule;

class InteractionModuleManager {

public:
    InteractionModuleManager();
    ~InteractionModuleManager();
    QList<quarre::InteractionModule*> getInteractionModulesAccesses() const;
    void setActiveModule(quarre::InteractionModule *module);
    quarre::InteractionModule* getActiveModule() const;
    void setControl(quarre::Control *controller);

private:
    QList<quarre::InteractionModule*> am_interaction_modules;
    quarre::InteractionModule *r_active_module;
    quarre::Control *r_control;

};

}

#endif // MODULEMANAGER_H
