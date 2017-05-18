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
    m_combo_box(new QComboBox) {

    loadNetworkPresets();
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *title = new QLabel("select network");
    QDialogButtonBox *button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(title, 0, Qt::AlignLeft);
    layout->addWidget(m_combo_box, 0, Qt::AlignLeft);
    layout->addWidget(m_line_edit, 0, Qt::AlignLeft);
    layout->addWidget(button_box, 0, Qt::AlignLeft);

    setBackgroundRole(QPalette::Dark);

    connect(button_box, SIGNAL(accepted()), this, SLOT(onOk()));
    connect(button_box, SIGNAL(rejected()), this, SLOT(onCancel()));
    connect(m_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(processIndexChange(int)));
}

void NetworkPopupWindow::loadNetworkPresets()
{
    QFile loaded_network_presets(":/network/hosts_ip.json");
    if(!loaded_network_presets.open(QIODevice::ReadOnly))
        qDebug() << "error: couldn't open hosts_ip.json";
    else qDebug() << "hosts_ip.json succesfully loaded!";

    QJsonParseError error;
    QByteArray saved_data = loaded_network_presets.readAll();
    QJsonDocument loaded_jsondoc = QJsonDocument::fromJson(saved_data, &error);
    if(loaded_jsondoc.isNull())
    {
        qDebug() << error.errorString();
        return;
    }

    am_network_presets = loaded_jsondoc.array();
    for(int i = 0; i < am_network_presets.count(); i++)
    {
        m_combo_box->addItem(am_network_presets[i].toObject()["name"].toString());
    }

    m_combo_box->setCurrentIndex(0);
    processIndexChange(0);
}

void NetworkPopupWindow::processIndexChange(int index)
{
    QJsonObject chosen_preset = am_network_presets[index].toObject();
    QString address_display = chosen_preset["ip"].toString() + ":" +
            QString::number(chosen_preset["port"].toInt());
    m_line_edit->setText(address_display);
}

void NetworkPopupWindow::onOk()
{
    QString host_address = m_line_edit->text();
    emit networkHostChange(host_address);
    this->close();
}

void NetworkPopupWindow::onCancel()
{
    this->close();
}

NetworkPopupWindow::~NetworkPopupWindow() {}

