#include "textviewer.h"
#include <QLayout>
#include <QScreen>
#include <QApplication>


using namespace arbre_integral;

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

    QFile loaded_interactions(":/projects/arbre_integral/textes.json");
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
            m_texts << text.toString(); }}

    m_current_text->setText(m_texts[0]);

    QObject::connect(this, SIGNAL(touchedModuleLeftSide()), this, SLOT(processModuleLeftTouch()));
    QObject::connect(this, SIGNAL(touchedModuleRightSide()), this, SLOT(processModuleRightTouch()));

}

TextViewer::~TextViewer() {}

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
                if(touchPoint.pos().x() <= width()/5.f) emit touchedModuleLeftSide();
                else if(touchPoint.pos().x() >= width() - width()/5.f) emit touchedModuleRightSide();
            } break; }
        } break; }
    default: return QWidget::event(event); }
    return true;
}

void TextViewer::processModuleLeftTouch() {
    if(m_index > 0) {
        m_index--;
        m_current_text->setText(m_texts[m_index]);
        r_control->processModuleCallback("/read_index", m_index, false);}}

void TextViewer::processModuleRightTouch() {
    if(m_index < m_texts.size() - 1) {
        m_index++;
        m_current_text->setText(m_texts[m_index]);
        r_control->processModuleCallback("/read_index", m_index, false);}}

quarre::InteractionModuleEnum TextViewer::getModuleEnumReference() { return quarre::AI_TEXTVIEWER; }
void TextViewer::startModule() {}
void TextViewer::stopModule() {}
QList<quarre::QGestureEnum> TextViewer::getQGestureRequirements() {
    QList<quarre::QGestureEnum> empty_list; return empty_list; }
QList<quarre::QRawSensorDataEnum> TextViewer::getQRawSensorDataRequirements() {
    QList<quarre::QRawSensorDataEnum> empty_list; return empty_list; }
void TextViewer::onReceivedGesture(quarre::QGestureEnum gesture) {}
void TextViewer::onReceivedSensorData(quarre::QRawSensorDataEnum sensor, qreal value) {}
void TextViewer::onReceivedMiscData(QString sender, qreal value) {
    if(sender == "/read_index") {
        m_index = value;
        m_current_text->setText(m_texts[m_index]);}}
