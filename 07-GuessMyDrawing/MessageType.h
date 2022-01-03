#ifndef MESSAGETYPE_H
#define MESSAGETYPE_H

#include <QString>

class MessageType {
public:
  inline static const QString TYPE = "type";
  inline static const QString MESSAGE_SENDER = "sender";

  inline static const QString CANVAS_MESSAGE = "canvas_message";
  inline static const QString TEXT_MESSAGE = "text_message";

  inline static const QString USER_JOINED = "user_joined";
  inline static const QString USER_LEFT = "user_left";

  inline static const QString USERNAME = "username";

  inline static const QString UNKNOW = "unknown";

  inline static const QString CONTENT = "content";

  inline static const QString JOIN_ROOM = "join_room";
  inline static const QString CREATE_ROOM = "create_room";
  inline static const QString LEAVE_ROOM = "leave_room";
  inline static const QString ROOM_NAME = "room_name";

  inline static const QString DURATION = "duration";

  inline static const QString CHOOSE_WORD = "choose_word";
  inline static const QString GET_ROOMS = "get_rooms";

  inline static const QString CANVAS_SOCKET = "canvas_socket";
  inline static const QString MESSAGE_SOCKET = "message_socket";

  inline static const QString NEW_HOST = "new_host";

  inline static const QString START = "start";
  inline static const QString GAME_OVER = "game_over";

  inline static const QString ID = "id";
};

#endif // MESSAGETYPE_H
