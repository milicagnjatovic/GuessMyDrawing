#ifndef SERVERMESSAGEPARSER_H
#define SERVERMESSAGEPARSER_H

#include<QJsonObject>
#include "../MessageType.h"
#include "ServerMessageEnum.h"
#include <QVector>


class ServerMessageParser
{
public:
    ServerMessageParser();

    QJsonObject toStartMessage();
    QJsonObject toUserJoinedMessage(QString &username);
    QJsonObject toJoinRoomMessage(QString &roomName);
    QJsonObject toGameOverMessage();
    QJsonObject toNewHostMessage();
    QJsonObject toUserLeftMessage(QString username);

    ServerMessageType getTypeFromMessage(const QJsonObject& message);
    QJsonObject toGetRoomsMessage(const QString& rooms);
    QVector<QString> fromJoinRoomMessage(const QJsonObject& message);
    QVector<QString> fromChooseWordMessage(const QJsonObject& message);
    QVector<QString> fromCreateRoomMessage(const QJsonObject& message);
};

#endif // SERVERMESSAGEPARSER_H
