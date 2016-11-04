#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QtWidgets>

#define MODULE_SIZE_RATIO 0.95

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_central_widget(new QWidget(this)),
    m_main_layout(new QVBoxLayout(m_central_widget)),
    m_stacked_widget(new QStackedWidget),
    m_combo_box(new QComboBox),
    m_connect_button(new QPushButton("connect to server")),
    m_label_id(new QLabel("ID: " + QString::number(0))),
    m_next_interaction_title(new QLabel("néant")),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    setWindowTitle("QUARRE PHONE USER WINDOW");

    // SCREEN_SIZE
    QScreen *screen = QApplication::screens().at(0);
    QSize screen_size = screen->availableSize();
    qreal dpi = screen->logicalDotsPerInch();
    qreal screen_width = screen_size.width();
    qreal ratio_font = screen_width*288/(dpi*1440);
    qreal ratio = screen_width/1440.f;

    setFixedSize(screen_size); // lock to full screen

    // DEBUG
    qDebug() << "available size, width: " << screen_width;
    qDebug() << "available size: height: " << screen_size.height();
    qDebug() << "dpi: " << dpi;

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
    m_connect_button->setMinimumHeight(50);
    info_layout_1->addWidget(m_connect_button, 0, Qt::AlignCenter);
    info_layout_1->addWidget(m_label_id, 0, Qt::AlignCenter);

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
    QFont label_button("Arial", 14 * ratio_font, -1);
    QFont label_it("Arial", 13 * ratio_font, -1, true);
    QFont label_bold("Arial", 15 * ratio_font, QFont::Bold, false);

    m_label_id->setFont(label_font);
    _next_interaction_title->setFont(label_it);
    _remaining_time->setFont(label_it);
    m_next_interaction_title->setFont(label_font);
    m_curr_interaction_title->setFont(label_bold);
    m_curr_interaction_descr->setFont(label_font);

    // SIGNAL / SLOTS UI CONNECTIONS
   // QObject::connect(m_connect_button, SIGNAL(pressed()), r_control, SLOT(registerToServer()));
    QObject::connect(m_combo_box, SIGNAL(activated(int)), m_stacked_widget, SLOT(setCurrentIndex(int)));

}

MainWindow::~MainWindow() {
    delete ui;
}
