#include "client.h"
#include "../MessageType.h"
#include <iostream>
#include <utility>

Client::Client(QString name, QObject *parent):
  QObject(parent),
  mName(std::move(name)),
  messageSocket(new QTcpSocket(this)),
  parser(new MessageParser())
{
  // connect and disconnect
  connect(messageSocket, &QTcpSocket::connected, this, &Client::connectedMessage);
  connect(messageSocket, &QTcpSocket::disconnected, this, &Client::disconnectedMessage);


  // slot to take care of Reading messsages
  connect(messageSocket, &QTcpSocket::readyRead, this, &Client::MessageReadyRead);

  connect(messageSocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
}

Client::~Client()
{
  delete messageSocket;
  delete parser;
}

void Client::connectToServer(const QHostAddress &adress, quint16 port)
{
  messageSocket->connectToHost(adress, port);
  this->adress = adress;
  this->port = port;
}

void Client::disconnectFromHost()
{
  messageSocket->disconnectFromHost();
}

void Client::send(const QString &text)
{
  sendMessage(parser->textMessage(text, mName));
}

void Client::joinRoom(QString &username, QString &roomName)
{
  this->mName = username;
  sendMessage(parser->joinRoomMessage(username, roomName));
}

void Client::createRoom(QString &username, QString &room_name, int duration)
{
  this->mName = username;
  sendMessage(parser->createRoomMessage(username, room_name, duration));
}

void Client::leaveRoom()
{
  sendMessage(parser->leaveRoomMessage());
  this->imHost = false;
  this->shouldBecomeHost = false;
}


void Client::chooseWord(QString &word)
{
  sendMessage(parser->chooseWordMessage(word));
}

void Client::getRooms()
{
  sendMessage(parser->getRoomsMessage());
}

void Client::sendCanvas(QString& canvas)
{
  sendMessage(parser->canvasMessage(canvas));
}

void Client::reconnect()
{
  connectToServer(this->adress, this->port);
}


void Client::MessageReadyRead()
{
  QByteArray data;
  data = messageSocket->readAll();

  QList<QByteArray> dataVec = data.split('}'); // split by json end

  for (auto &jsonData: dataVec) {
      // if we don't have valid json beggining there's no point of going further
    if(jsonData.isEmpty() || jsonData[0] != '{')
      continue;
    jsonData.append('}'); // add } which we removed while splitting

    QJsonParseError parseError;
    const QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);
    if(parseError.error == QJsonParseError::NoError){
        // data is valid json
        if (doc.isObject()) // if it's json object we can recieve it
          jsonReceived(doc.object());
        else
          std::cerr << "DOC IS NOT JSON OBJECT" << std::endl;
      }
    else{
      std::cerr << "PARSING JSON ERR : " << parseError.errorString().toStdString() << std::endl;
      }
    }
}

void Client::connectedMessage()
{
   std::cout << "message socket connected" << std::endl;
}

void Client::disconnectedMessage()
{
  std::cout << "message socket disconnected" << std::endl;
}

void Client::error(QAbstractSocket::SocketError socketError)
{
  Q_UNUSED(socketError);
//  QString *s = new QString("Something went wrong with cnnnection. Please try again.");
  emit errorConnecting();
}

void Client::jsonReceived(const QJsonObject &doc)
{
  QVector<QString> ret;
  MessageReceivedType type = parser->parseReceivedMessage(doc, ret);

  switch (type) {
    case MessageReceivedType::TEXT_MESSAGE:{
        if (ret.size() != 2){
            std::cerr << "Missing argument for text message" << std::endl;
            return;
          }
        emit messageReceived(ret[0], ret[1]);
        break;
      }

    case MessageReceivedType::USER_JOINED:{
        if (ret.size() != 1){
            std::cerr << "Missing argument for user joined" << std::endl;
            return;
          }
        emit userJoined(ret[0]);
        break;
      }

    case MessageReceivedType::USER_LEFT:{
        if (ret.size() != 1){
            std::cerr << "Missing argument for user left" << std::endl;
            return;
          }
        emit userLeft(ret[0]);
        break;
      }

    case MessageReceivedType::GET_ROOMS:{
        auto *room_list = new QVector<QString>;
        for(QString& r : ret){
            room_list->push_back(r);
          }
        emit roomList(room_list);
        break;
      }

    case MessageReceivedType::JOINED_ROOM:{
        bool bJoined = true;
        if (ret.length() != 0)
          bJoined = false; // in ret is message that it wasnt able to join
        emit joinedRoom(bJoined);
        break;
      }

    case MessageReceivedType::NEW_HOST: {
      shouldBecomeHost = true; // can't become host yet, because as soon as plaeyr becomes host it'll star sendin canvas messages, and may loose choose word message
      emit youAreNewHost();
      break;
      }

    case MessageReceivedType::GAME_OVER: {
        imHost = false;
        emit gameOver();
        break;
      }

    case MessageReceivedType::GAME_START: {
        if (shouldBecomeHost){
            imHost = true;
            shouldBecomeHost = false;
          }
        emit startGame();
        break;
      }

    case MessageReceivedType::CANVAS_MESSAGE:{
        if (ret.size() != 1){
            std::cerr << "Missing argument for canvas message" << std::endl;
            return;
          }
//        QByteArray b = QByteArray::fromBase64(ret[0].toUtf8());
        emit canvasReceived(ret[0]);
        break;
      }

    case MessageReceivedType::ERROR: {
        std::cerr << "Error occured" << std::endl;
//        for (auto i : ret)
//          std::cout << i.toStdString() << std::endl;
      }
    }
}


void Client::sendMessage(const QJsonObject& message)
{
  auto msg = QJsonDocument(message).toJson(QJsonDocument::Compact);
  messageSocket->write(msg);
  messageSocket->flush();
}
