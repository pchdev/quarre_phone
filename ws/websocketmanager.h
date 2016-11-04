#ifndef WEBSOCKETMANAGER_H
#define WEBSOCKETMANAGER_H

#include <QWebSocket>

namespace quarre {

class WebSocketManager : public QObject {

    Q_OBJECT

public:
    WebSocketManager(QUrl url);
    ~WebSocketManager();
    void sendMessage(QString message) const;

protected slots:
    void onConnected() const;
    void parseReceivedTextMessage(QString message);
    void parseReceivedBinaryMessage(QByteArray message);

private:
    QWebSocket *m_socket;
};

}

#endif // WEBSOCKETMANAGER_H
