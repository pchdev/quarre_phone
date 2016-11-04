#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>

#include "../interactions/modules/interactionmodule.h"
#include "../interactions/modules/modulemanager.h"
#include "../ws/websocketmanager.h"
#include "../os/osbridge.h"
#include "../sensors/sensormanager.h"
#include "../data/userdatamanager.h"
#include "../views/mainwindow.h"

class MainWindow;

namespace quarre {

class InteractionModule;
class SensorManager;
class UserDataManager;

class Control : public QObject {

    Q_OBJECT

public:
    Control();
    ~Control();
    void initModuleLinking();

public slots:
    void onServerIpChange(QString ip) const;
    void onServerConnectionRequest() const;
    void onServerConnectionConfirmationRequest() const;
    void onReceivedId(int id) const;
    void onInterruptAll() const;
    void onScenarioBeginning() const;
    void onScenarioEnding() const;
    void onIncomingInteraction(QList<int> interaction) const;
    void onInteractionBeginning(int interaction_id) const;
    void onInteractionEnding(int interaction_id) const;

private:
    QList<InteractionModule*> r_interaction_modules;
    quarre::OSBridge *r_os_control;
    quarre::WebSocketManager *r_ws_manager;
    quarre::SensorManager *r_sensor_manager;
    quarre::UserDataManager *r_data_manager;
    MainWindow *r_mainwindow;
};
}

#endif // CONTROL_H
