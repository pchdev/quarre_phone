#ifndef INTERACTIONDATABASE_H
#define INTERACTIONDATABASE_H

#include "../models/interaction.h"
#include "../../ext-libs/jsoncpp/json/json.h"
#include <fstream>

// BRIDGE BETWEEN .JSON FORMAT INTERACTIONS & C++ OBJECTS

namespace quarre {

class Interaction;
class InteractionDatabase {

public:
    InteractionDatabase();
    ~InteractionDatabase();
    quarre::Interaction* getInteraction(int id) const;

private:
    QList<quarre::Interaction*> am_interactions;

};

}

#endif // INTERACTIONDATABASE_H
