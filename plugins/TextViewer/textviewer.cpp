#include "textviewer.h"
#include <QLayout>
#include <QScreen>
#include <QApplication>
#include <QtDebug>

QString TextViewer::getModuleIdentifier() {
    return QStringLiteral("AI_TEXTVIEWER");}

QList<quarre::QGestureEnum> TextViewer::getQGestureRequirements() {
    return EMPTY_QGESTUREREQLIST;}

QList<quarre::QRawSensorDataEnum> TextViewer::getQRawSensorDataRequirements() {
    return EMPTY_QRAWSENSORREQLIST;}

QList<QString> TextViewer::getCustomResponderAddresses() {
    return QList<QString>() << "/read_index";}

TextViewer::~TextViewer() {}
void TextViewer::start() {}
void TextViewer::stop() {}
void TextViewer::onReceivedGesture(quarre::QGestureEnum gesture) {}
void TextViewer::onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value) {}
TextViewer::TextViewer() :
    m_current_text(new QLabel("nil")),
    m_index(0) {

    setAttribute(Qt::WA_AcceptTouchEvents);

    // get screen infos
    QScreen *screen = QApplication::screens().at(0);
    qreal dpi = screen->logicalDotsPerInch();
    QSize screen_size = screen->availableSize();
    qreal screen_width = screen_size.width();
    qreal ratio_font = screen_width*288/(dpi*1440);
    qreal ratio = screen_width/1440.f;

    // layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    QFont font("Arial", 20 * ratio_font, -1, true);
    m_current_text->setWordWrap(false);
    m_current_text->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    m_current_text->setFont(font);
    m_current_text->setFixedWidth(screen_width * 0.95);
    layout->addWidget(m_current_text, 0, Qt::AlignCenter);

    // json parser for texts

    QFile loaded_interactions("assets:/arbre-integral-textes.json");
    if(!loaded_interactions.open(QIODevice::ReadOnly)) {
        qDebug() << "error: couldn't open arbre_integral textes.json";
    } else {  qDebug() << "textes.json was succesfully opened";}

    QJsonParseError error;
    QByteArray saved_data = loaded_interactions.readAll();
    QJsonDocument loaded_json = QJsonDocument::fromJson(saved_data, &error);

    // json doc should return an array
    if(loaded_json.isArray()) qDebug() << "file is array";
    else if(loaded_json.isObject()) qDebug() << "file is object";
    else if(loaded_json.isNull()) {
        qDebug() << "file is null";
        qDebug() << error.errorString();}

    QJsonArray main_array = loaded_json.array();
    foreach(QJsonValue cerne, main_array) {
        foreach(QJsonValue text, cerne.toArray()) {
            m_texts << text.toString();
        }
    }

    m_current_text->setText(m_texts[0]);

}

bool TextViewer::event(QEvent *event) {
    switch(event->type()) {
    case QEvent::TouchBegin: {
        QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent*>(event)->touchPoints();
        foreach(const QTouchEvent::TouchPoint &touchPoint, touchPoints) {
            switch(touchPoint.state()) {
            case Qt::TouchPointStationary: break;
            default: {
                qDebug() << width();
                qDebug() << touchPoint.pos().x();
                if(touchPoint.pos().x() <= width()/5.f) this->processModuleLeftTouch();
                else if(touchPoint.pos().x() >= width() - width()/5.f) this->processModuleRightTouch();
            } break; }
        } break; }
    default: return QWidget::event(event); }
    return true;
}

void TextViewer::processModuleLeftTouch() {
    if(m_index > 0) {
        m_index--;
        m_current_text->setText(m_texts[m_index]);
        emit sendBackData("/read_index", m_index, false);
    }
}

void TextViewer::processModuleRightTouch() {
    if(m_index < m_texts.size() - 1) {
        m_index++;
        m_current_text->setText(m_texts[m_index]);
        emit sendBackData("/read_index", m_index, false);
    }
}

void TextViewer::onReceivedCustomData(QString sender, QList<qreal> values) {
    if(sender == "/phone/read_index") {
        m_index = values[0];
        m_current_text->setText(m_texts[m_index]);
    }
}
