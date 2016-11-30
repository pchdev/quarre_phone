#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QComboBox>

#include "countdownwidget.h"
#include "networkpopupwindow.h"
#include "interactions/modules/modulemanager.h"
#include "interactions/modules/interactionmodule.h"
#include "interactions/models/interaction.h"

// fwds
namespace Ui {
class MainWindow;
}

namespace quarre {
class InteractionModule;
class CountdownWidget;
class Interaction;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, quarre::Control *control = 0);
    ~MainWindow();
    void updateCurrentInteraction(quarre::Interaction *interaction);
    void updateNextInteraction(quarre::Interaction *interaction, int countdown_value);
    void voidNextInteraction();
    void voidCurrentInteraction();
    void stackInteractionModules(QList<quarre::InteractionModule*> interaction_modules);
    void updateUserId(int id);
    void setConnected();
    void setDisconnected();
    void setController(quarre::Control *control);
    void startScenarioTimer();
    void stopScenarioTimer();

protected:
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

protected slots:
    void onPrefsButtonPressing();
    void updateTimerTick();

private:
    Ui::MainWindow *ui;
    quarre::Control *r_control;
    quarre::CountdownWidget *m_next_countdown;
    quarre::CountdownWidget *m_current_countdown;
    QStackedWidget *m_stacked_widget;
    QComboBox *m_combo_box;
    QWidget *m_central_widget;
    QPushButton *m_connect_button;
    QPushButton *m_prefs_button;
    QVBoxLayout *m_main_layout;
    QLabel *m_label_id;
    QLabel *m_next_interaction_title;
    QLabel *m_curr_interaction_title;
    QLabel *m_curr_interaction_descr;
    quarre::NetworkPopupWindow *m_network_popup;
    QTimer *m_scenario_timer;
    int m_timer_count;
};

#endif // MAINWINDOW_H
