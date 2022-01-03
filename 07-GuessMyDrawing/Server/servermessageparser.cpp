#include "servermessageparser.h"
#include <QVector>

ServerMessageParser::ServerMessageParser()
{

}

QJsonObject ServerMessageParser::toStartMessage()
{
    QJsonObject message;
    message[MessageType::TYPE] = MessageType::START;

    return message;
}

QJsonObject ServerMessageParser::toUserJoinedMessage(QString &username)
{
    QJsonObject message;
    message[MessageType::TYPE] = MessageType::USER_JOINED;
    message[MessageType::USERNAME] = username;

    return message;
}

QJsonObject ServerMessageParser::toJoinRoomMessage(QString &roomName)
{
    QJsonObject message;
    message[MessageType::TYPE] = MessageType::JOIN_ROOM;
    message[MessageType::ROOM_NAME] =roomName;

    return message;
}

QJsonObject ServerMessageParser::toGameOverMessage()
{
    QJsonObject message;
    message[MessageType::TYPE] = MessageType::GAME_OVER;

    return message;
}

QJsonObject ServerMessageParser::toNewHostMessage()
{
    QJsonObject message;
    message[MessageType::TYPE] = MessageType::NEW_HOST;

    return message;
}

QJsonObject ServerMessageParser::toUserLeftMessage(QString username)
{
    QJsonObject message;
    message[MessageType::TYPE] = MessageType::USER_LEFT;
    message[MessageType::USERNAME] = username;

    return message;
}

QJsonObject ServerMessageParser::toGetRoomsMessage(const QString& rooms) {
    QJsonObject message;
    message[MessageType::TYPE] = QString(MessageType::GET_ROOMS);
    message[MessageType::CONTENT] = rooms;
    return message;
}

ServerMessageType ServerMessageParser::getTypeFromMessage(const QJsonObject& message) {
    const QJsonValue type = message.value(MessageType::TYPE);
    if (type.toString().compare(MessageType::TEXT_MESSAGE) == 0) {
        return ServerMessageType::TEXT_MESSAGE;
    }

    if (type.toString().compare(MessageType::CREATE_ROOM) == 0) {
        return ServerMessageType::CREATE_ROOM;
    }

    if (type.toString().compare(MessageType::JOIN_ROOM) == 0) {
        return ServerMessageType::JOIN_ROOM;
    }

    if (type.toString().compare(MessageType::LEAVE_ROOM) == 0) {
        return ServerMessageType::LEAVE_ROOM;
    }

    if (type.toString().compare(MessageType::CHOOSE_WORD) == 0) {
        return ServerMessageType::CHOOSE_WORD;
    }

    if (type.toString().compare(MessageType::GET_ROOMS) == 0) {
        return ServerMessageType::GET_ROOMS;
    }

    if (type.toString().compare(MessageType::CANVAS_MESSAGE) == 0) {
        return ServerMessageType::CANVAS_MESSAGE;
    }
    return ServerMessageType::ERROR;
}

QVector<QString> ServerMessageParser::fromJoinRoomMessage(const QJsonObject& message) {
    QVector<QString> ret;
    const QJsonValue username = message.value(MessageType::USERNAME);
    ret.append(username.toString());
    const QJsonValue room_name = message.value(MessageType::ROOM_NAME);
    ret.append(room_name.toString());
    return ret;
}

QVector<QString> ServerMessageParser::fromChooseWordMessage(const QJsonObject& message) {
    QVector<QString> ret;
    const QJsonValue word = message.value(MessageType::CONTENT);
    ret.append(word.toString());
    return ret;
}

QVector<QString> ServerMessageParser::fromCreateRoomMessage(const QJsonObject& message) {
    QVector<QString> ret;
    const QJsonValue username = message.value(MessageType::USERNAME);
    ret.append(username.toString());
    const QJsonValue room_name = message.value(MessageType::ROOM_NAME);
    ret.append(room_name.toString());
    const QJsonValue duration = message.value(MessageType::DURATION);
    ret.append(duration.toString());
    return ret;
}





























