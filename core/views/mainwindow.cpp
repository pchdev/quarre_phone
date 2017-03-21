#include "mainwindow.h"
#include <QtDebug>
#include <QtWidgets>

#define MODULE_SIZE_RATIO 0.95

MainWindow::MainWindow(QWidget *parent, quarre::Control *control) :
    QMainWindow(parent),
    m_central_widget(new QWidget(this)),
    m_main_layout(new QVBoxLayout(m_central_widget)),
    m_stacked_widget(new QStackedWidget),
    m_combo_box(new QComboBox),
    m_connect_button(new QPushButton("connect to server")),
    m_prefs_button(new QPushButton("server_prefs")),
    m_label_id(new QLabel("0")),
    m_next_interaction_title(new QLabel("néant")),
    r_control(control),
    m_timer_count(0),
    m_scenario_timer(new QTimer(this)),
    m_network_popup(new quarre::NetworkPopupWindow(this)) {

    setWindowTitle("QUARRE PHONE USER WINDOW");

    // SCREEN_SIZE
    QScreen *screen = QApplication::screens().at(0);
    QSize screen_size = screen->availableSize();
    qreal dpi = screen->logicalDotsPerInch();
    qreal screen_width = screen_size.width();
    qreal ratio_font = screen_width*288/(dpi*1440);
    qreal ratio = screen_width/1440.f;

    setFixedSize(screen_size); // lock to full screen

    // MAIN LAYOUT DEFINITIONS
    this->setCentralWidget(m_central_widget);
    QVBoxLayout *info_layout = new QVBoxLayout;

    // CATCH INTERACTION MODULES

    // MAIN LAYOUT COMPONENTS
    m_main_layout->addLayout(info_layout, 0);
    m_main_layout->addWidget(m_stacked_widget, 0, Qt::AlignCenter);

    // INFO LAYOUT COMPONENTS

    // 1st line - server infos
    QHBoxLayout *info_layout_1 = new QHBoxLayout;
    m_connect_button->setMinimumHeight(15);
    info_layout_1->addWidget(m_connect_button, 0, Qt::AlignCenter);
    info_layout_1->addWidget(m_label_id, 0, Qt::AlignCenter);
    info_layout_1->addWidget(m_prefs_button, 0, Qt::AlignCenter);

    // 2nd line - next interaction infos
    QGridLayout *info_layout_2 = new QGridLayout;
    QLabel *_next_interaction_title = new QLabel("prochaine \n interaction: ");
    _next_interaction_title->setAlignment(Qt::AlignCenter);
    m_next_countdown = new quarre::CountdownWidget(ratio_font*0.75);
    m_next_countdown->setMinimumSize(height()*0.1 * ratio_font, height()*0.1 * ratio_font);

    info_layout_2->addWidget(_next_interaction_title, 1, 1, 1, 1, Qt::AlignCenter);
    info_layout_2->addWidget(m_next_interaction_title, 1, 2, 1, 1, Qt::AlignCenter);
    info_layout_2->addWidget(m_next_countdown, 1, 3, 1, 1, Qt::AlignCenter);

    // rest: current interaction infos
    QLabel *_remaining_time = new QLabel("Interaction actuelle - temps restant");
    m_curr_interaction_title = new QLabel("Aucune interaction");
    m_curr_interaction_descr = new QLabel("veuillez patienter jusqu'à la prochaine interaction...");
    m_curr_interaction_descr->setAlignment(Qt::AlignCenter);
    m_curr_interaction_descr->setWordWrap(true);
    m_curr_interaction_descr->setMinimumWidth(width() * 0.9);
    m_current_countdown = new quarre::CountdownWidget(ratio_font);
    m_current_countdown->setMinimumSize(height()*0.15*ratio_font, height()*0.15*ratio_font);

    // LAYOUT CONNECTIONS
    info_layout->addLayout(info_layout_1);
    info_layout->addLayout(info_layout_2);
    info_layout->addWidget(m_current_countdown, 0, Qt::AlignCenter);
    info_layout->addWidget(m_curr_interaction_title, 0, Qt::AlignCenter);
    info_layout->addWidget(m_curr_interaction_descr, 0, Qt::AlignCenter);

    // FONTS
    QFont label_font("Arial", 13*ratio_font, -1);
    QFont label_button("Arial", 12 * ratio_font, -1);
    QFont label_it("Arial", 13 * ratio_font, -1, true);
    QFont label_bold("Arial", 15 * ratio_font, QFont::Bold, false);
    QFont label_timer("Arial", 17 * ratio_font, -1);

    m_label_id->setFont(label_timer);
    _next_interaction_title->setFont(label_it);
    _remaining_time->setFont(label_it);
    m_next_interaction_title->setFont(label_font);
    m_curr_interaction_title->setFont(label_bold);
    m_curr_interaction_descr->setFont(label_font);
    m_connect_button->setFont(label_button);
    m_prefs_button->setFont(label_button);

    // SIGNAL / SLOTS UI CONNECTIONS
    QObject::connect(m_prefs_button, SIGNAL(pressed()), this, SLOT(onPrefsButtonPressing()));
    QObject::connect(m_combo_box, SIGNAL(activated(int)), m_stacked_widget, SLOT(setCurrentIndex(int)));
    QObject::connect(m_scenario_timer, SIGNAL(timeout()), this, SLOT(updateTimerTick()));

}

MainWindow::~MainWindow() {}

#ifdef Q_OS_ANDROID

void MainWindow::keyReleaseEvent(QKeyEvent *event) { // override to block android back key
    qDebug() << event->key();
    if(event->key() == Qt::Key_Back) {
        event->accept();}}

#endif

void MainWindow::onPrefsButtonPressing() {
    m_network_popup->exec();}

void MainWindow::stackInteractionModules(QList<quarre::InteractionModule*> interaction_modules) {
    foreach(quarre::InteractionModule *module, interaction_modules) {
        m_stacked_widget->addWidget(module);
        m_combo_box->addItem(tr("Interaction Module"));
        module->setFixedSize(width()*0.95, width() * 0.95);
    }

    m_combo_box->activated(1);
}

void MainWindow::updateCurrentInteraction(quarre::Interaction *interaction, int module_index) {
    m_current_countdown->triggerTimer(interaction->getCurrentLength());
    m_curr_interaction_title->setText(interaction->getTitle());
    m_curr_interaction_descr->setText(interaction->getDescription());
    m_combo_box->activated(module_index);

}

void MainWindow::updateNextInteraction(quarre::Interaction *interaction, int countdown_value) {
    m_next_countdown->triggerTimer(countdown_value);
    m_next_interaction_title->setText(interaction->getTitle());}

void MainWindow::voidCurrentInteraction() {
    m_current_countdown->stopTimer();
    m_curr_interaction_title->setText("Aucune interaction");
    m_curr_interaction_descr->setText("veuillez patienter jusqu'à la prochaine interaction...");
    m_combo_box->activated(3);}

void MainWindow::voidNextInteraction() {
    m_next_countdown->stopTimer();
    m_next_interaction_title->setText("néant");}

void MainWindow::updateUserId(int id) {
    m_label_id->setText("USER ID " + QString::number(id));}

void MainWindow::setConnected() {
    m_connect_button->setText("connected");
    m_connect_button->setStyleSheet("color: black;");
    QObject::disconnect(m_connect_button, SIGNAL(pressed()), r_control, SLOT(processServerConnectionRequest()));}

void MainWindow::setDisconnected() {
    m_connect_button->setText("DISCONNECTED");
    m_connect_button->setStyleSheet("color: red;");
    QObject::connect(m_connect_button, SIGNAL(pressed()), r_control, SLOT(processServerConnectionRequest()));}

void MainWindow::setController(quarre::Control *control) {
    r_control = control;
    m_current_countdown->setControl(control);
    QObject::connect(m_network_popup, SIGNAL(networkHostChange(QString)),
                     r_control, SLOT(processServerIpChange(QString)));
    QObject::connect(m_connect_button, SIGNAL(pressed()),
                     r_control, SLOT(processServerConnectionRequest()));
}

void MainWindow::startScenarioTimer() { m_scenario_timer->start(1000); }
void MainWindow::stopScenarioTimer() {
    m_scenario_timer->stop();
    m_timer_count = 0;
    m_label_id->setText("00:00");
}
void MainWindow::updateTimerTick() {
    m_timer_count++;
    int min = m_timer_count / 60;
    int sec = m_timer_count % 60;
    m_label_id->setText(QString::number(min) + ":" + QString::number(sec));
}

quarre::InteractionModule* MainWindow::getDisplayedModule() const {
    quarre::InteractionModule* module = qobject_cast<quarre::InteractionModule*>(m_stacked_widget->currentWidget());
    return module;
}
