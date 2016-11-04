#include "websocketmanager.h"

using namespace quarre;

WebSocketManager::WebSocketManager(QUrl url) : m_socket(new QWebSocket) {
    QObject::connect(m_socket, SIGNAL(connected()), this, SLOT(onConnected()));
    m_socket->open(url);
}

WebSocketManager::~WebSocketManager() {
    delete m_socket;
}

void WebSocketManager::sendMessage(QString message) const {

    // double check against osc specs & then send...
    m_socket->sendTextMessage(message);
}

void WebSocketManager::onConnected() const {
    QObject::connect(m_socket, SIGNAL(textMessageReceived(QString)), this, SLOT(parseReceivedTextMessage(QString)));
    QObject::connect(m_socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(parseReceivedBinaryMessage(QByteArray)));
    m_socket->sendTextMessage(QStringLiteral("Hello Quarrè Server!"));
}

void WebSocketManager::parseReceivedTextMessage(QString message) {

}

void WebSocketManager::parseReceivedBinaryMessage(QByteArray message) {}

