#include "core/control/control.h"
#include "core/control/scenariofollower.h"
#include "core/interactions/interactiondatabase.h"
#include "core/modules/modulemanager.h"
#include "core/network/websocketmanager.h"
#include "core/platform/osbridge.h"
#include "core/views/mainwindow.h"

#include <QtDebug>
#include <QApplication>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    QUrl default_url(QStringLiteral("ws://192.168.2.118:8080"));

    // initialize modules
    quarre::WebSocketManager ws_manager(default_url, true);
    quarre::InteractionDatabase interaction_db;
    interaction_db.loadInteractionNamespace("arbre-integral");

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
                                 &sensor_manager, &scenario_follower,
                                 &interaction_db,
                                 &module_manager, &w);

    // exec application
    ws_manager.connect();
    w.show();
    return a.exec();

}
