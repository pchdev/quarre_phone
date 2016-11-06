#include "control.h"

using namespace quarre;

Control::Control() {}

Control::~Control() {}

void Control::initModuleLinking(OSBridge *os_control,
                                WebSocketManager *ws_manager,
                                SensorManager *sensor_manager,
                                UserDataManager *data_manager,
                                ScenarioFollower *scenario_follower,
                                InteractionDatabase *interaction_db,
                                InteractionModuleManager *module_manager,
                                MainWindow *mainwindow) {

    // set refs
    r_os_control = os_control;
    r_ws_manager = ws_manager;
    r_sensor_manager = sensor_manager;
    r_data_manager = data_manager;
    r_scenario_follower = scenario_follower;
    r_interaction_db = interaction_db;
    r_module_manager = module_manager;
    r_mainwindow = mainwindow;

}

void Control::setInteractionModulesReferences(QList<InteractionModule *> interaction_modules) {
    ar_interaction_modules = interaction_modules;
    foreach(quarre::InteractionModule *module, ar_interaction_modules) {
        module->setController(this);
    }
}

void Control::moduleValueCallback(QString address, qreal value, bool vibrate) const {
    r_ws_manager->sendMessage(address + " " + value);
    if(vibrate) r_os_control->vibrate(100);
}

// SLOTS -- TBI

void Control::onServerIpChange(QString ip) const {
    QString address = "ws://" + ip;
    QUrl url(address);
    r_ws_manager->reConnect(url);
}

void Control::onServerConnectionRequest() const {
    r_ws_manager->connect();
}

void Control::onServerConnectionConfirmationRequest() const {}
// send back a msg to ensure that the connection has been made succesfully - obsolete with ws

void Control::onReceivedId(int id) const {
    r_data_manager->setUserId(id);
    r_mainwindow->updateUserId(id);
}

void Control::onInterruptAll() const {}
// reset application interaction management

void Control::onScenarioBeginning() const {}
void Control::onScenarioEnding() const {} // just in case

void Control::onIncomingInteraction(QList<int> interaction) const {

    // parse list // TBI
    int countdown_value;
    int interaction_length;
    // check the database for the interaction // TBI
    quarre::Interaction *interactionptr;

    // update the interaction's associated length
    interactionptr->setCurrentLength(interaction_length);
    // update the mainwindow
    r_mainwindow->updateNextInteraction(interactionptr, countdown_value);
    // update the scenario follower
    r_scenario_follower->setNextInteraction(interactionptr);
    // vibrate
    r_os_control->vibrate(200);

}

void Control::onInteractionBeginning(int interation_id) const {

    quarre::Interaction *interactionptr = r_scenario_follower->getCurrentInteraction();

    r_mainwindow->updateCurrentInteraction(interactionptr);
    quarre::InteractionModule *module = ar_interaction_modules[interaction_id];
    module->startModule();

    QList<quarre::QGestureEnum> qgesture_polling_req = interactionptr->getGesturePollingRequirements();
    QList<quarre::QRawSensorDataEnum> qrawsensordata_polling_req =
            interactionptr->getRawSensorDataPollingRequirements();

    foreach(quarre::QGestureEnum &gesture, qgesture_polling_req) {
        r_sensor_manager->startGestureRecognition();
    }

    foreach(quarre::QRawSensorDataEnum &data, qrawsensordata_polling_req) {
    }

    r_scenario_follower->beginNextInteraction();
    r_os_control->vibrate(500);
}

// check the validness of interaction id
// check for sensor or gesture polling needs
// dispatch the interaction to mainwindow
// activate the matching module
// update the scenario follower
// vibrate

void Control::onInteractionEnding(int interaction_id) const {
    quarre::Interaction *interactionptr;

}
// check the database for the interaction
// check for sensor or gesture polling needs and shut them off
// deactivate the matching module
// update mainwindow
// update scenario follower
// set interaction length to 0

void Control::moduleValueCallback(QString address, qreal value, bool vibrate) const {

}

void Control::gestureCallback(QGestureEnum gesture, qreal value) const {

}

void Control::sensorCallback(QRawSensorDataEnum sensor, qreal value) const {

}




