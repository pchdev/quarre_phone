#include "websocketmanager.h"
#include <QtDebug>

using namespace quarre;

WebSocketManager::WebSocketManager(QUrl url, bool connect_on_startup) :
    m_socket(new QWebSocket),
    is_connected(false),
    m_server_url(url) {
    QObject::connect(m_socket, SIGNAL(connected()), this, SLOT(onConnected()));
    QObject::connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    QObject::connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(onError(QAbstractSocket::SocketError)));
}

WebSocketManager::~WebSocketManager() {delete m_socket;}
void WebSocketManager::onError(QAbstractSocket::SocketError) { qDebug() << m_socket->errorString();}
void WebSocketManager::setServerUrl(QUrl url) {m_server_url = url;}
void WebSocketManager::parseReceivedBinaryMessage(QByteArray message) {}

void WebSocketManager::connect() {
    m_socket->close();
    if(!is_connected) {
        m_socket->open(m_server_url);
    }
}

void WebSocketManager::reConnect(QUrl host_url) {
    qDebug() << "reconnecting at: " << host_url;
    delete m_socket;
    m_socket = new QWebSocket;
    QObject::connect(m_socket, SIGNAL(connected()), this, SLOT(onConnected()));
    QObject::connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    QObject::connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(onError(QAbstractSocket::SocketError)));
    m_socket->open(host_url);
}

void WebSocketManager::sendMessage(QString message, bool addPhonePrefix) const {
    // double check against osc specs & then send...
    if(addPhonePrefix) message = "/phone" + message;
    m_socket->sendTextMessage(message);
}

void WebSocketManager::onConnected() {
    emit connectedToServer();
    is_connected = true;
    QObject::connect(m_socket, SIGNAL(textMessageReceived(QString)), this, SLOT(parseReceivedTextMessage(QString)));
    QObject::connect(m_socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(parseReceivedBinaryMessage(QByteArray)));
}

void WebSocketManager::onDisconnected() {
    is_connected = false;
    emit disconnectedFromServer();
}

void WebSocketManager::parseReceivedTextMessage(QString message) {

    qDebug() << "ws msg received: " << message;
    QStringList splitted_message = message.split(' ');
    QString address = splitted_message.at(0);

    // matching signal emission
    if(address == "/id/request") emit requestedWebSocketId();
    else if(address == "/phone/scenario/reset") emit reset();
    else if(address == "/phone/test/accelerometers") emit requestedAccelerometersTest();
    else if(address == "/phone/test/rotation") emit requestedRotationTest();
    else if(address == "/phone/test/azimuth") emit requestedCompassTest();
    else if(address == "/phone/scenario/is_active") {
        if(splitted_message.at(1) == "1") emit scenarioHasStarted();
        else if(splitted_message.at(1) == "0") emit scenarioHasEnded();
    }
    else if(address == "/phone/interactions/next/incoming") {

        QString first_int = splitted_message.at(1); first_int.remove('['); first_int.remove(',');
        QString second_int = splitted_message.at(2); second_int.remove(',');
        QString third_int = splitted_message.at(3); third_int.remove(']');

        int id = first_int.toInt();
        int length = second_int.toInt();
        int starting_time = third_int.toInt();

        QList<int> parsed_list;
        parsed_list << id << length << starting_time;
        emit incomingInteraction(parsed_list);
    }

    else if(address == "/phone/interactions/next/begin") emit beginningInteraction(splitted_message.at(1).toInt());
    else if(address == "/phone/interactions/current/end") emit endingInteraction(splitted_message.at(1).toInt());
    else if(address == "/phone/read_index") emit readIndexUpdate(splitted_message.at(1).toInt());

}



