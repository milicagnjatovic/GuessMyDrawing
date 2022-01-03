#ifndef SERVER_H
#define SERVER_H

#include <QString>
#include <QMap>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include "room.h"
#include "thread.h"
#include "ServerMessageEnum.h"

class Server : public QTcpServer {
 Q_OBJECT
 public:
    explicit Server(QObject *parent = 0);
    ~Server();
    void startServer();
 signals:

 public slots:
    void parseMessage(const QJsonObject& message, Thread* thread);
 protected:
    void incomingConnection(qintptr socketDescriptor);
 private:
    Room* getRoomFromThread(Thread* thread);
    void broadcastMessage(const QJsonObject& message, Thread* thread);
    void createRoom(const QString& username, const QString& room_name, int duration);
    void joinRoom(const QString& username, const QString& room_name, Thread* thread);
    void leaveRoom(Thread* thread);
    void chooseWord(const QString& word, Thread* thread);
    QString getRooms();
    void broadcastCanvas(const QJsonObject& message, Thread* thread);

    ServerMessageParser* _serverMessageParser;
    QMap<QString, Room*> _rooms;
    QVector<Thread*> _clients;
};

#endif // SERVER_H

