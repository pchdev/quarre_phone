#include "networkpopupwindow.h"

#include <QDialogButtonBox>
#include <QLayout>
#include <QLabel>
#include <QComboBox>
#include <QtDebug>

using namespace quarre;

NetworkPopupWindow::NetworkPopupWindow(QWidget *parent) :
    QDialog(parent),
    selected_item(0),
    item_selection(0){

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *title = new QLabel("select network");
    QComboBox *combo_box = new QComboBox;
    QDialogButtonBox *button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    combo_box->addItem("SCRIME");
    combo_box->addItem("SMC");
    combo_box->addItem("HOME-BX");
    combo_box->addItem("HOME-TS");
    layout->addWidget(title, 0, Qt::AlignLeft);
    layout->addWidget(combo_box, 0, Qt::AlignLeft);
    layout->addWidget(button_box, 0, Qt::AlignLeft);

    connect(combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(onItemSelection(int)));
    connect(button_box, SIGNAL(accepted()), this, SLOT(onOk()));
    connect(button_box, SIGNAL(rejected()), this, SLOT(onCancel()));

}

void NetworkPopupWindow::onItemSelection(int index) {
    item_selection = index;
}

void NetworkPopupWindow::onOk() {
    selected_item = item_selection;
    selected_item = 0;
    QString host_address;

    switch(item_selection) {
    case 0: host_address = "147.210.110.84:8080"; break;
    case 1: host_address = "192.168.2.118:8080"; break;
    case 2: host_address = "192.168.1.10:8080"; break;}

    emit networkHostChange(host_address);
    qDebug() << "host has changed signal from network popup";
    this->close();
}

void NetworkPopupWindow::onCancel() {
    selected_item = 0;
    item_selection = 0;
    this->close();
}

NetworkPopupWindow::~NetworkPopupWindow() {}

