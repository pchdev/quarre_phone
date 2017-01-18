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
#include <QtDebug>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    //QUrl default_url(QStringLiteral("ws://192.168.1.25:8080"));
    //QUrl default_url(QStringLiteral("ws://147.210.110.84:8080"));
    QUrl default_url(QStringLiteral("ws://192.168.2.118:8080"));

    // initialize modules
    quarre::UserDataManager data_manager;
    quarre::WebSocketManager ws_manager(default_url, true);
    quarre::InteractionDatabase interaction_db;
    quarre::ScenarioFollower scenario_follower;
    quarre::InteractionModuleManager module_manager;
    quarre::OSBridge os_bridge;
    quarre::SensorManager sensor_manager;

    // initialize the main controller
    quarre::Control controller;

    // initialize the main window view
    MainWindow w;

    // misc.
    qRegisterMetaType<QList<int> >("QList<int>");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");

    // initialize connections
    controller.initModuleLinking(&os_bridge, &ws_manager,
                                 &sensor_manager, &data_manager,
                                 &scenario_follower, &interaction_db,
                                 &module_manager, &w);

    // exec application
    ws_manager.connect();
    w.show();
    return a.exec();
}
