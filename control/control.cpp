#include "control.h"
#include <QtDebug>

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

    r_sensor_manager->setController(this);

}

void Control::setInteractionModulesReferences(QList<InteractionModule *> interaction_modules) {
    ar_interaction_modules = interaction_modules;
    foreach(quarre::InteractionModule *module, ar_interaction_modules) {
        module->setController(this);
    }
}

// SLOTS

void Control::processServerIpChange(QString ip) const {
    qDebug() << ip;
    QString address = "ws://" + ip;
    QUrl url(address);
    r_ws_manager->reConnect(url);
}

void Control::processServerConnectionRequest() const { r_ws_manager->connect();}
void Control::processReceivedIdFromServer(int id) const {
    r_data_manager->setUserId(id);
    r_mainwindow->updateUserId(id);
}
void Control::processGlobalInterruption() const {}
// reset application interaction management

void Control::processScenarioBeginning() const {}
void Control::processScenarioEnding() const {} // just in case
void Control::processIncomingInteraction(QList<int> interaction) const { // [id, length, starting_time]

    // parse list // TBI
    int interaction_id = interaction[0];
    int interaction_length = interaction[1];
    int interaction_starting_time = interaction[2];

    // check the database for the interaction // TBI // should return a pointer to the interaction
    quarre::Interaction *interactionptr = r_interaction_db->getInteraction(interaction_id);

    // update the interaction's associated length
    interactionptr->setCurrentLength(interaction_length);

    // update the mainwindow
    r_mainwindow->updateNextInteraction(interactionptr, interaction_starting_time);

    // update the scenario follower
    r_scenario_follower->setNextInteraction(interactionptr);

    // vibrate
    r_os_control->vibrate(200);

}

void Control::processingInteractionBeginning(int interaction_id) const {

    // check the validity of interaction id, set it to active
    quarre::Interaction *interaction = r_scenario_follower->getNextInteraction();
    if(interaction_id != interaction->getId()) return;
    interaction->setActive(true);

    // if current interaction has not ended, shut it down
    if(r_scenario_follower->getCurrentInteraction() != nullptr) {
        this->processInteractionEnding(r_scenario_follower->getCurrentInteraction()->getId());
    }

    // check for sensor or gesture polling needs, pass them to the sensor manager
    r_sensor_manager->setRecognizedGestures(interaction->getGesturePollingRequirements());
    r_sensor_manager->setPolledSensors(interaction->getRawSensorDataPollingRequirements());

    // get matching module, set it as the active module in the module manager, activate it
    quarre::InteractionModule *module = ar_interaction_modules[interaction->getModuleId()];
    r_module_manager->setActiveModule(module);
    module->startModule();

    // update the current interaction in the mainwindow
    r_mainwindow->updateCurrentInteraction(interaction);

    // poll sensors & gestures
    r_sensor_manager->startGestureRecognition();
    r_sensor_manager->startSensorPolling();

    // update the scenario follower
    r_scenario_follower->beginNextInteraction();

    // vibrate
    r_os_control->vibrate(500);

    // void next_interaction
    r_mainwindow->voidNextInteraction();
}

void Control::processInteractionEnding(int interaction_id) const {

    // double check id
    quarre::Interaction *interaction = r_scenario_follower->getCurrentInteraction();
    if(interaction_id != interaction->getId()) return;

    // deactivate interaction
    interaction->setActive(false);
    interaction->setCurrentLength(NULL);

    // stop sensor manager activity, void its current targets

    QList<quarre::QGestureEnum> empty_gesture_enum;

    r_sensor_manager->stopGestureRecognition();
    r_sensor_manager->stopSensorPolling();
    r_sensor_manager->voidPolledSensors();
    r_sensor_manager->voidRecognizedGestures();

    // stop module
    quarre::InteractionModule *module = r_module_manager->getActiveModule();
    r_module_manager->setActiveModule(nullptr);
    module->stopModule();

    // void interaction from scenario follower and mainwindow
    r_mainwindow->voidCurrentInteraction();
    r_scenario_follower->voidCurrentInteraction();

    r_os_control->vibrate(50);

}

// check the database for the interaction
// check for sensor or gesture polling needs and shut them off
// deactivate the matching module
// update mainwindow
// update scenario follower
// set interaction length to 0

void Control::processModuleCallback(QString address, qreal value, bool vibrate) const {
    if(vibrate) r_os_control->vibrate(50);
    r_ws_manager->sendMessage(address + " " + QString::number(value));
}

void Control::processGestureCallback(QGestureEnum gesture, qreal value) const {

    QString message = "/gestures/" + quarre::qgesture_names[gesture] + " " + QString::number(value);
    r_ws_manager->sendMessage(message);
    qDebug() << message;
    quarre::InteractionModule *module = r_module_manager->getActiveModule();
    qDebug() << "got active module";
    module->onReceivedGesture(gesture);
    qDebug() << "updated module ui";
    r_os_control->vibrate(100);
}

void Control::processSensorCallback(QRawSensorDataEnum sensor, qreal value) const {
    QString message = "/sensors" + quarre::qrawsensor_names[sensor] + " " + QString::number(value);
    r_ws_manager->sendMessage(message);
    quarre::InteractionModule *module = r_module_manager->getActiveModule();
    if(!module->getQRawSensorDataRequirements().isEmpty()) module->onReceivedSensorData(sensor, value);
}

void Control::processServerConnection() const {
    r_mainwindow->setConnected();}
void Control::processServerDisconnection() const {
    r_mainwindow->setDisconnected(); }

// speedy implementation, this is really bad...
void Control::processReadIndexUpdate(int index) const {
    if(r_module_manager->getActiveModule() == nullptr) return;
    quarre::InteractionModule *module = r_module_manager->getActiveModule();
    if(module->getModuleEnumReference() == quarre::AI_TEXTVIEWER)
        module->onReceivedSensorData(quarre::Accelerometer_x, index);}
