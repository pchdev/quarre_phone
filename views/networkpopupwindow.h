#ifndef NETWORKPOPUPWINDOW_H
#define NETWORKPOPUPWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>

namespace quarre {

class NetworkPopupWindow : public QDialog {

    Q_OBJECT

public:
    NetworkPopupWindow(QWidget *parent = 0);
    ~NetworkPopupWindow();

private:
    QComboBox *m_combo_box;
    QLineEdit *m_line_edit;

signals:
    void networkHostChange(QString ip);

protected slots:
    void onOk();
    void onCancel();

};
}

#endif // NETWORKPOPUPWINDOW_H
