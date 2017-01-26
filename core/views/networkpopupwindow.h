#ifndef NETWORKPOPUPWINDOW_H
#define NETWORKPOPUPWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

namespace quarre {

class NetworkPopupWindow : public QDialog {

    Q_OBJECT

public:
    NetworkPopupWindow(QWidget *parent = 0);
    ~NetworkPopupWindow();

private:
    void loadNetworkPresets();
    QComboBox *m_combo_box;
    QLineEdit *m_line_edit;
    QJsonArray am_network_presets;

signals:
    void networkHostChange(QString ip);

protected slots:
    void onOk();
    void onCancel();
    void processIndexChange(int index);

};
}

#endif // NETWORKPOPUPWINDOW_H
