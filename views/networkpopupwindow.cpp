#include "networkpopupwindow.h"

#include <QDialogButtonBox>
#include <QLayout>
#include <QLabel>
#include <QComboBox>
#include <QtDebug>
#include <QPushButton>

using namespace quarre;

NetworkPopupWindow::NetworkPopupWindow(QWidget *parent) :
    QDialog(parent),
    m_line_edit(new QLineEdit),
    m_combo_box(new QComboBox){

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *title = new QLabel("select network");
    QDialogButtonBox *button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    m_combo_box->addItem("SCRIME");
    m_combo_box->addItem("SMC");
    m_combo_box->addItem("HOME-BX");
    m_combo_box->addItem("HOME-TS");
    m_combo_box->addItem("OARA");
    layout->addWidget(title, 0, Qt::AlignLeft);
    layout->addWidget(m_combo_box, 0, Qt::AlignLeft);
    layout->addWidget(m_line_edit, 0, Qt::AlignLeft);
    layout->addWidget(button_box, 0, Qt::AlignLeft);

    setBackgroundRole(QPalette::Dark);

    connect(button_box, SIGNAL(accepted()), this, SLOT(onOk()));
    connect(button_box, SIGNAL(rejected()), this, SLOT(onCancel()));
}

void NetworkPopupWindow::onOk() {

    QString host_address;

    if(m_line_edit->text().isEmpty()) {
        switch(m_combo_box->currentIndex()) {
        case 0: host_address = "147.210.110.84:8080"; break;
        case 1: host_address = "192.168.2.118:8080"; break;
        case 2: host_address = "192.168.1.10:8080"; break;
        case 3: host_address = "192.168.1.26:8080"; break;}
    } else { host_address = m_line_edit->text();}

    emit networkHostChange(host_address);
    qDebug() << "host has changed signal from network popup";
    this->close();
}

void NetworkPopupWindow::onCancel() {
    this->close();
}

NetworkPopupWindow::~NetworkPopupWindow() {}

