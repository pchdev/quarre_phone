#include "scenariofollower.h"

using namespace quarre;

ScenarioFollower::ScenarioFollower() :
    m_scenario_status(0),
    m_next_interaction(0),
    m_current_interaction(0) {}

ScenarioFollower::~ScenarioFollower() {}

void ScenarioFollower::voidCurrentInteraction() { m_current_interaction = 0; }
void ScenarioFollower::voidNextInteraction() { m_next_interaction = 0; }
void ScenarioFollower::beginNextInteraction() {
    m_current_interaction = m_next_interaction;
    m_next_interaction = 0;
}

void ScenarioFollower::setNextInteraction(quarre::Interaction *interaction) {
    m_next_interaction = interaction;
}

void ScenarioFollower::forceNextInteraction(quarre::Interaction *interaction) {} // is it really still relevant here ?

quarre::Interaction* ScenarioFollower::getCurrentInteraction() const { return m_current_interaction; }
quarre::Interaction* ScenarioFollower::getNextInteraction() const { return m_next_interaction; }
