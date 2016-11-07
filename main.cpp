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
    QUrl default_url("ws://147.210.110.84:8080");

    // initialize modules
    quarre::UserDataManager data_manager;
    quarre::WebSocketManager ws_manager(default_url, false);
    qDebug() << "WebSocket ok";
    quarre::InteractionDatabase interaction_db;
    qDebug() << "Interaction DB OK";
    quarre::ScenarioFollower scenario_follower;
    qDebug() << "Scenario follower ok";
    quarre::InteractionModuleManager module_manager;
    qDebug() << "InteractionModuleManager ok";
    quarre::OSBridge os_bridge;
    qDebug() << "OSBridge ok";
    quarre::SensorManager sensor_manager;
    qDebug() << "SensorManager ok";

    // initialize the main controller
    quarre::Control controller;
    qDebug() << "controller ok";

    // initialize the main window view
    MainWindow w;
    qDebug() << "mainwindow ok";

    // misc.
    qRegisterMetaType<QList<int> >("QList<int>");

    // initialize connections
    controller.initModuleLinking(&os_bridge, &ws_manager,
                                 &sensor_manager, &data_manager,
                                 &scenario_follower, &interaction_db,
                                 &module_manager, &w);
    qDebug() << "module linking ok";
    controller.setInteractionModulesReferences(module_manager.getInteractionModulesAccesses());
    qDebug() << "interaction modules ref ok";
    w.stackInteractionModules(module_manager.getInteractionModulesAccesses());
    qDebug() << "stack interaction modules ref ok";

    QObject::connect(&ws_manager, SIGNAL(beginningInteraction(int)), &controller, SLOT(onInteractionBeginning(int)));
    QObject::connect(&ws_manager, SIGNAL(endingInteraction(int)), &controller, SLOT(onInteractionEnding(int)));
    QObject::connect(&ws_manager, SIGNAL(incomingInteraction(QList<int>)), &controller, SLOT(onIncomingInteraction(QList<int>)));
    QObject::connect(&ws_manager, SIGNAL(interruptAll()), &controller, SLOT(onInterruptAll()));
    QObject::connect(&ws_manager, SIGNAL(receivedIdFromServer(int)), &controller, SLOT(onReceivedId(int)));

    // exec application
    w.show();
    return a.exec();
}
