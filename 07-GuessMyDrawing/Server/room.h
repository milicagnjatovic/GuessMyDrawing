#ifndef ROOM_H
#define ROOM_H

#include<iostream>
#include<string>
#include<map>
#include<unordered_map>
#include<QString>
#include<QMap>
#include<QJsonObject>
#include "thread.h"
#include "servermessageparser.h"

class Room
{
private:
    QString name;
    QMap<QString, Thread*> players;
    QString chosenWord;
    int numOfPlayers = players.size();
    int duration;
    QString host;
    bool gameIsStarted;
    ServerMessageParser *parser;
    bool noMorePlayers;

    void chooseRandomHost();
    void gameOver(Thread* t);


public:
    //server call constructor for room and sends in constructor name of host
    Room(QString firstHost, QString roomName, int duration);
    ~Room();

    void broadcastMessage(const QJsonObject& message, Thread *t);
    void broadcastCanvas(const QJsonObject& message, Thread *t);

    void start();
    void setDuration(int newDuration);
    void leaveRoom(Thread* thread);

    bool usernameIsTaken(QString username);
    void setWordAndStartGame(const QString &newChosenWord);
    void checkChatWord(QString word, Thread* senderUser);
    void joinClient(QString username, Thread* thread);

    QString getWord() {return chosenWord;}
};

#endif // ROOM_H
