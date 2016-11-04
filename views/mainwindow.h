#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QComboBox>

#include "countdownwidget.h"
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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateWithNewInteraction(quarre::Interaction);

private:
    Ui::MainWindow *ui;
    quarre::Control *r_control;
    quarre::CountdownWidget *m_next_countdown;
    quarre::CountdownWidget *m_current_countdown;
    QList<quarre::InteractionModule*> ar_interaction_modules;
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
};

#endif // MAINWINDOW_H