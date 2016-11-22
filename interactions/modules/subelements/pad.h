#ifndef PAD_H
#define PAD_H

#include <QWidget>
#include <QEvent>
#include <QTouchEvent>
#include "../interactionmodule.h"

namespace quarre {

class Pad : public QWidget {

    Q_OBJECT

public:
    Pad(quarre::InteractionModule *parent = 0, uint8_t id = 0);
    ~Pad();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    bool event(QEvent *event) Q_DECL_OVERRIDE;

private:
    void sendStateUpdateToParent();
    quarre::InteractionModule *r_parent;
    uint8_t m_size;
    bool m_state;
    uint8_t m_id;
};

}

#endif // PAD_H
