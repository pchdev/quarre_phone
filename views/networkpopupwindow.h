#ifndef NETWORKPOPUPWINDOW_H
#define NETWORKPOPUPWINDOW_H

#include <QDialog>

namespace quarre {

class NetworkPopupWindow : public QDialog {

    Q_OBJECT

public:
    NetworkPopupWindow(QWidget *parent = 0);
    ~NetworkPopupWindow();

private:
    int selected_item;
    int item_selection;

signals:
    void networkHostChange(QString ip);

protected slots:
    void onItemSelection(int index);
    void onOk();
    void onCancel();

};
}

#endif // NETWORKPOPUPWINDOW_H
