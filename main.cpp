#include <QApplication>

#include "ws/websocketmanager.h"
#include "os/osbridge.h"
#include "sensors/sensormanager.h"
#include "control/control.h"
#include "control/scenariofollower.h"
#include "data/userdatamanager.h"
#include "interactions/modules/modulemanager.h"
#include "interactions/db/interactiondatabase.h"
#include "views/mainwindow.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    QUrl default_url("ws://192.168.0.1:8080");

    // initialize user data manager
    quarre::UserDataManager data_manager;

    // initialize websocket
    quarre::WebSocketManager ws_manager(default_url);

    // initialize interaction database
    quarre::InteractionDatabase interaction_db;

    // initialize scenario follower
    quarre::ScenarioFollower scenario_follower;

    // initialize module manager
    quarre::InteractionModuleManager module_manager;

    // initialize the os bridge
    quarre::OSBridge os_bridge;

    // initialize the sensor manager
    quarre::SensorManager sensor_manager;

    // initialize the controller
    quarre::Control controller;

    // initialize the main view
    MainWindow w;
    w.show();

    return a.exec();
}
