#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>

#include "../modules/modulemanager.h"
#include "../interactions/interactiondatabase.h"
#include "../network/websocketmanager.h"
#include "../platform/osbridge.h"
#include "../sensors/sensormanager.h"
#include "../views/mainwindow.h"
#include "scenariofollower.h"
#include "../../plugins/quarreplugininterface.h"

class MainWindow;

namespace quarre {

class InteractionModule;
class SensorManager;
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
                           quarre::ScenarioFollower *scenario_follower,
                           quarre::InteractionDatabase *interaction_db,
                           quarre::InteractionModuleManager *module_manager,
                           MainWindow *mainwindow);

public slots: // core functions -- should not be accessed by plugins!!
    void processServerIpChange(QString ip) const;
    void processServerConnectionRequest() const;
    void processServerConnection() const;
    void processServerDisconnection() const;
    //void processReceivedIdFromServer(int id) const;
    void processScenarioBeginning() const;
    void processScenarioEnding() const;
    void processIncomingInteraction(QList<int> interaction) const;
    void processingInteractionBeginning(int interaction_id) const;
    void processInteractionEnding(int interaction_id) const;
    void processReset() const;
    void processWebSocketIdRequest() const;
    void processSensorCallback(quarre::QRawSensorDataEnum sensor, qreal value) const;
    void processGestureCallback(quarre::QGestureEnum gesture, qreal value) const;
    void processMiscMessage(QString address, QList<qreal> values) const;

    // plugin related, linking is done with signal-slots connections with plugins-modules
    void processModuleCallback(QString address, qreal value, bool vibrate) const;
    void processModuleCallback(QString address, bool vibrate) const;

private:
    void forceInteractionBeginning(int interaction_id) const;
    quarre::OSBridge *r_os_control;
    quarre::WebSocketManager *r_ws_manager;
    quarre::SensorManager *r_sensor_manager;
    quarre::ScenarioFollower *r_scenario_follower;
    quarre::InteractionDatabase *r_interaction_db;
    quarre::InteractionModuleManager *r_module_manager;
    MainWindow *r_mainwindow;
};
}

#endif // CONTROL_H
