#ifndef SCENARIOFOLLOWER_H
#define SCENARIOFOLLOWER_H

#include "../interactions/interaction.h"

namespace quarre {

class ScenarioFollower {

public:
    ScenarioFollower();
    ~ScenarioFollower();
    void voidCurrentInteraction();
    void voidNextInteraction();
    void forceNextInteraction(quarre::Interaction *interaction);
    void beginNextInteraction();
    void setNextInteraction(quarre::Interaction *interaction);
    quarre::Interaction* getCurrentInteraction() const;
    quarre::Interaction* getNextInteraction() const;

private:
    int m_scenario_status;
    quarre::Interaction* m_current_interaction;
    quarre::Interaction* m_next_interaction;
};

}

#endif // SCENARIOFOLLOWER_H
