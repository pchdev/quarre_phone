#include "control.h"
#include <QtDebug>

using namespace quarre;

Control::Control() {}
Control::~Control() {}

void Control::initModuleLinking(OSBridge *os_control,
                                WebSocketManager *ws_manager,
                                SensorManager *sensor_manager,
                                ScenarioFollower *scenario_follower,
                                InteractionDatabase *interaction_db,
                                InteractionModuleManager *module_manager,
                                MainWindow *mainwindow)
{
    // set refs
    r_os_control = os_control;
    r_ws_manager = ws_manager;
    r_sensor_manager = sensor_manager;
    r_scenario_follower = scenario_follower;
    r_interaction_db = interaction_db;
    r_module_manager = module_manager;
    r_mainwindow = mainwindow;

    r_sensor_manager->setController(this);
    r_mainwindow->setController(this);

    // bind modules to ui & controller
    QList<quarre::InteractionModule*> modules = r_module_manager->getInteractionModulesReferences();
    foreach(quarre::InteractionModule *module, modules) {
        connect(module, SIGNAL(sendBackData(QString,qreal,bool)), this, SLOT(processModuleCallback(QString, qreal, bool)));
    }

    r_mainwindow->stackInteractionModules(modules);

    connect(r_ws_manager, SIGNAL(incomingInteraction(QList<int>)), this, SLOT(processIncomingInteraction(QList<int>)));
    connect(r_ws_manager, SIGNAL(beginningInteraction(int)), this, SLOT(processingInteractionBeginning(int)));
    connect(r_ws_manager, SIGNAL(endingInteraction(int)), this, SLOT(processInteractionEnding(int)));
    connect(r_ws_manager, SIGNAL(connectedToServer()), this, SLOT(processServerConnection()));
    connect(r_ws_manager, SIGNAL(disconnectedFromServer()), this, SLOT(processServerDisconnection()));
    connect(r_ws_manager, SIGNAL(reset()), this, SLOT(processReset()));
    connect(r_ws_manager, SIGNAL(scenarioHasStarted()), this, SLOT(processScenarioBeginning()));
    connect(r_ws_manager, SIGNAL(scenarioHasEnded()), this, SLOT(processScenarioEnding()));
    connect(r_ws_manager, SIGNAL(requestedWebSocketId()), this, SLOT(processWebSocketIdRequest()));
    connect(r_ws_manager, SIGNAL(customMessageReceived(QString,QList<qreal>)), this, SLOT(processMiscMessage(QString,QList<qreal>)));

}

// SERVER RELATED

void Control::processServerIpChange(QString ip) const
{
    QUrl url("ws://" + ip);
    r_ws_manager->reConnect(url);
}

void Control::processServerConnection() const
{
    r_mainwindow->setConnected();
}

void Control::processServerDisconnection() const
{
    r_mainwindow->setDisconnected();
}

void Control::processWebSocketIdRequest() const
{
    r_ws_manager->sendMessage("/id phone", false);
}

void Control::processServerConnectionRequest() const
{
    r_ws_manager->connect();
}

void Control::processReset() const
{
    // void current and next interaction
    if(r_scenario_follower->getCurrentInteraction() != nullptr)
    {
        int id = r_scenario_follower->getCurrentInteraction()->getId();
        this->processInteractionEnding(id);
    }

    r_mainwindow->voidCurrentInteraction();
    r_scenario_follower->voidNextInteraction();
    r_mainwindow->voidNextInteraction();
    r_os_control->vibrate(25);
}

// INTERACTION & SCENARIO RELATED

void Control::processScenarioBeginning() const
{
    r_mainwindow->startScenarioTimer();
}

void Control::processScenarioEnding() const
{
    r_mainwindow->stopScenarioTimer();
}

void Control::processIncomingInteraction(QList<int> interaction) const
{ // [id, length, starting_time]

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
    r_os_control->vibrate(100);
}

void Control::processingInteractionBeginning(int interaction_id) const
{
    // if interaction is unannounced, force its triggering
    if(r_scenario_follower->getNextInteraction() == nullptr)
    {
        this->forceInteractionBeginning(interaction_id);
        return;
    }

    // check the validity of interaction id, set it to active
    quarre::Interaction *interaction = r_scenario_follower->getNextInteraction();
    if(interaction_id != interaction->getId()) return;
    interaction->setActive(true);

    // if current interaction has not ended, shut it down
    if(r_scenario_follower->getCurrentInteraction() != nullptr)
    {
        this->processInteractionEnding(r_scenario_follower->getCurrentInteraction()->getId());
    }

    // check for sensor or gesture polling needs, pass them to the sensor manager
    r_sensor_manager->setRecognizedGestures(interaction->getGesturePollingRequirements());
    r_sensor_manager->setPolledSensors(interaction->getRawSensorDataPollingRequirements());

    // get matching module, set it as the active module in the module manager, activate it
    QString module_identifier = interaction->getModuleId();
    quarre::InteractionModule *module = r_module_manager->getModuleReferenceByName(module_identifier);
    qDebug() << module->getModuleIdentifier();
    int module_index = r_module_manager->getModuleIndexByName(module_identifier);
    r_module_manager->setActiveModule(module);
    module->start();

    // update the current interaction in the mainwindow
    r_mainwindow->updateCurrentInteraction(interaction, module_index);

    // poll sensors & gestures
    r_sensor_manager->startGestureRecognition();
    r_sensor_manager->startSensorPolling();

    // update the scenario follower
    r_scenario_follower->beginNextInteraction();

    // vibrate
    r_os_control->vibrate(250);

    // void next_interaction
    r_mainwindow->voidNextInteraction();
}

void Control::forceInteractionBeginning(int interaction_id) const {}

void Control::processInteractionEnding(int interaction_id) const
{
    // double check id
    quarre::Interaction *interaction = r_scenario_follower->getCurrentInteraction();
    if(interaction == nullptr) return;
    if(interaction_id != interaction->getId()) return;

    // deactivate interaction
    interaction->setActive(false);
    interaction->setCurrentLength(NULL);

    // stop sensor manager activity, void its current targets
    r_sensor_manager->stopGestureRecognition();
    r_sensor_manager->stopSensorPolling();
    r_sensor_manager->voidPolledSensors();
    r_sensor_manager->voidRecognizedGestures();

    // stop module
    quarre::InteractionModule *module = r_module_manager->getActiveModule();
    r_module_manager->setActiveModule(nullptr);
    module->stop();

    // void interaction from scenario follower and mainwindow
    r_mainwindow->voidCurrentInteraction();
    r_scenario_follower->voidCurrentInteraction();

    r_os_control->vibrate(50);
}

// CALLBACKS & DATA PASSING

void Control::processModuleCallback(QString address, qreal value, bool vibrate) const
{
    if(vibrate) r_os_control->vibrate(25);
    r_ws_manager->sendMessage(address + " " + QString::number(value));
}

void Control::processModuleCallback(QString address, bool vibrate) const
{ // impulse only
    if(vibrate) r_os_control->vibrate(25);
    r_ws_manager->sendMessage(address);
}

void Control::processGestureCallback(QGestureEnum gesture, qreal value) const
{
    QString message = "/gestures/" + quarre::qgesture_names[gesture] + " " + QString::number(value);
    r_ws_manager->sendMessage(message);
    qDebug() << message;
    quarre::InteractionModule *module = r_module_manager->getActiveModule();
    module->onReceivedGesture(gesture);
    r_os_control->vibrate(50);
}

void Control::processSensorCallback(QRawSensorDataEnum sensor, qreal value) const
{
    QString message = "/sensors/" + quarre::qrawsensor_names[sensor] + " " + QString::number(value);
    r_ws_manager->sendMessage(message);
    quarre::InteractionModule *module = r_module_manager->getActiveModule();
    if(!module->getQRawSensorDataRequirements().isEmpty()) module->onReceivedSensorData(sensor, value);
}

void Control::processMiscMessage(QString address, QList<qreal> values) const
{
   qDebug() << address;
   quarre::InteractionModule *module = r_module_manager->getActiveModule();
   if(module == nullptr) module = r_mainwindow->getDisplayedModule();
   QList<QString> responder_addresses = module->getCustomResponderAddresses();
   qDebug() << "got custom addresses";
   foreach(QString rspaddress, responder_addresses) {
       if(address == rspaddress) {
           qDebug() << "found responder address";
           module->onReceivedCustomData(address, values);
       }
   }
}
