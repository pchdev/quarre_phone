#include "control.h"

using namespace quarre;

Control::Control() {}

Control::~Control() {}

void Control::initModuleLinking() {}

// SLOTS -- TBI

void Control::onServerIpChange(QString ip) const {} // signal emitted from view
// update user data manager
// update view

void Control::onServerConnectionRequest() const {} // signal emitted from view
// get registered url in data manager
// transmit it to web socket manager
// open url & connection

void Control::onServerConnectionConfirmationRequest() const {}
// send back a msg to ensure that the connection has been made succesfully

void Control::onReceivedId(int id) const {}
// update user data manager
// update mainwindow

void Control::onInterruptAll() const {}
// reset application interaction management

void Control::onScenarioBeginning() const {}
void Control::onScenarioEnding() const {} // just in case

void Control::onIncomingInteraction(QList<int> interaction) const {}
// check the database for the interaction
// update the interaction's associated length
// update the mainwindow
// update the scenario follower

void Control::onInteractionBeginning(int interation_id) const {}
// check the database for the interaction
// check for sensor or gesture polling needs
// dispatch the interaction to mainwindow
// activate the matching module
// update the scenario follower

void Control::onInteractionEnding(int interaction_id) const {}
// check the database for the interaction
// check for sensor or gesture polling needs and shut them off
// deactivate the matching module
// update mainwindow
// update scenario follower




