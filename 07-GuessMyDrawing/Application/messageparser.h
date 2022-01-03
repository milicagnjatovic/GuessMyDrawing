#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include "../MessageType.h"
#include "MessageReceivedEnum.h"
#include <QJsonObject>
#include <QByteArray>
#include <QVector>

class MessageParser
{
public:
  MessageParser();

  QJsonObject textMessage(const QString &text, const QString &name);
  QJsonObject joinRoomMessage(QString &username, QString &roomName);
  QJsonObject createRoomMessage(QString &username, QString &room_name, int duration);
  QJsonObject leaveRoomMessage();
  QJsonObject chooseWordMessage(QString &word);
  QJsonObject getRoomsMessage();
//  QJsonObject canvasMessage(QByteArray &canvas);
  QJsonObject canvasMessage(QString &canvas);

  MessageReceivedType parseReceivedMessage(const QJsonObject& message, QVector<QString> &ret);

private:
  bool isFieldValid(const QJsonValue& value);
};

#endif // MESSAGEPARSER_H
