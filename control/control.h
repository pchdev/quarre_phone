#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>

#include "../interactions/modules/interactionmodule.h"
#include "../interactions/modules/modulemanager.h"
#include "../interactions/db/interactiondatabase.h"
#include "../ws/websocketmanager.h"
#include "../os/osbridge.h"
#include "../sensors/sensormanager.h"
#include "../data/userdatamanager.h"
#include "../views/mainwindow.h"
#include "scenariofollower.h"

class MainWindow;

namespace quarre {

class InteractionModule;
class SensorManager;
class UserDataManager;
class InteractionModuleManager;
class ScenarioFollower;
class InteractionDatabase;

class Control : public QObject {

    Q_OBJECT

public:
    Control();
    ~Control();
    void initModuleLinking(quarre::OSBridge *os_control,
                           quarre::WebSocketManager *ws_manager,
                           quarre::SensorManager *sensor_manager,
                           quarre::UserDataManager *data_manager,
                           quarre::ScenarioFollower *scenario_follower,
                           quarre::InteractionDatabase *interaction_db,
                           quarre::InteractionModuleManager *module_manager,
                           MainWindow *mainwindow);

    void setInteractionModulesReferences(QList<InteractionModule*> interaction_modules);
    void processModuleCallback(QString address, qreal value, bool vibrate) const;
    void processGestureCallback(quarre::QGestureEnum gesture, qreal value) const;
    void processSensorCallback(quarre::QRawSensorDataEnum sensor, qreal value) const;

public slots:
    void processServerIpChange(QString ip) const;
    void processServerConnectionRequest() const;
    void processServerConnection() const;
    void processServerDisconnection() const;
    void processReceivedIdFromServer(int id) const;
    void processGlobalInterruption() const;
    void processScenarioBeginning() const;
    void processScenarioEnding() const;
    void processIncomingInteraction(QList<int> interaction) const;
    void processingInteractionBeginning(int interaction_id) const;
    void processInteractionEnding(int interaction_id) const;

private:
    QList<InteractionModule*> ar_interaction_modules;
    quarre::OSBridge *r_os_control;
    quarre::WebSocketManager *r_ws_manager;
    quarre::SensorManager *r_sensor_manager;
    quarre::UserDataManager *r_data_manager;
    quarre::ScenarioFollower *r_scenario_follower;
    quarre::InteractionDatabase *r_interaction_db;
    quarre::InteractionModuleManager *r_module_manager;
    MainWindow *r_mainwindow;
};
}

#endif // CONTROL_H
