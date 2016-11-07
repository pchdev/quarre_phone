#include "interactiondatabase.h"
#include <QtDebug>

using namespace quarre;


InteractionDatabase::InteractionDatabase() {

    //Json::Value interactions;
    //std::ifstream json_interactions_file("interactions.json", std::ifstream::binary);
    //json_interactions_file >> interactions;

    //qDebug() << interactions["interaction_1"]; // to be tested
}

InteractionDatabase::~InteractionDatabase() {}

quarre::Interaction* InteractionDatabase::getInteraction(int id) const {
    return am_interactions[id];
}

