#ifndef WEBSOCKETMANAGER_H
#define WEBSOCKETMANAGER_H

#include <QWebSocket>

namespace quarre {

class WebSocketManager : public QObject {

    Q_OBJECT

public:
    WebSocketManager(QUrl url, bool connect_on_startup);
    ~WebSocketManager();
    void sendMessage(QString message) const;
    void connect();
    void setServerUrl(QUrl url);
    void reConnect(QUrl host_url);

signals:
    void connectedToServer();
    void disconnectedFromServer();
    void interruptAll();
    void receivedIdFromServer(int);
    void requestedAccelerometersTest();
    void requestedEndingOfAccelerometersTest();
    void requestedRotationTest();
    void requestedEndingOfRotationTest();
    void requestedCompassTest();
    void requestedEndingOfCompassTest();
    void scenarioHasStarted();
    void scenarioHasEnded();
    void incomingInteraction(QList<int>);
    void beginningInteraction(int);
    void endingInteraction(int);
    void readIndexUpdate(int);
    void reset();

protected slots:
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError);
    void parseReceivedTextMessage(QString message);
    void parseReceivedBinaryMessage(QByteArray message);

private:
    QWebSocket *m_socket;
    QUrl m_server_url;
    bool is_connected;
};

}

#endif // WEBSOCKETMANAGER_H
