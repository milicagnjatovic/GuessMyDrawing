#include "room.h"
#include "../MessageType.h"
#include <unordered_map>
#include <QRandomGenerator>


Room::Room(QString firstHost, QString roomName, int duration): name(roomName), duration(duration), host(firstHost)
{
  gameIsStarted = false;
  parser = new ServerMessageParser();
}

Room::~Room()
{
    qDeleteAll(players);
    players.clear();
    delete parser;
}

void Room::setDuration(int newDuration)
{
    duration = newDuration;
}

void Room::leaveRoom(Thread* thread)
{

  QString name = "";

  for (auto i=players.begin(); i!=players.end(); i++){
    if (i.value() == thread){

        QJsonObject message = parser->toUserLeftMessage(i.key());

        //remove player from players map
        name = i.key();
        players.remove(i.key());
        broadcastMessage(message, thread);

        break;
      }
    }

    // if host left the game
    if (name.compare(host)==0){
      gameOver(thread);
      chooseRandomHost();
      return;
    }

    //if there are enough players left to continue the game
    if(players.size() < 2){
        gameOver(thread);

        // ako je host ostao sam onda mora da mu se kaze da je i dalje host, jer je izgubio "host" privilegije sa gameOver()
        QJsonObject message = parser->toNewHostMessage();
       // message[MessageType::TYPE] = MessageType::NEW_HOST;
        players[host]->send(message);
    }
}


bool Room::usernameIsTaken(QString username)
{
    if(players.contains(username)){
        return true;
    }

    return false;
}

void Room::setWordAndStartGame(const QString &newChosenWord)
{

  chosenWord = newChosenWord;
  if(players.size() >= 2)
      start();
}

void Room::checkChatWord(QString word, Thread* senderUser)
{
    if(word.compare(chosenWord)==0){
        QMapIterator<QString, Thread*> i(players);
        while (i.hasNext()) {
            i.next();
            if (i.value() == senderUser)
              host = i.key();
         }
        gameOver(senderUser);

        QJsonObject message = parser->toNewHostMessage();
       // message[MessageType::TYPE] = MessageType::NEW_HOST;
        senderUser->send(message);
    }

}


void Room::chooseRandomHost()
{

  int n = players.size();
  if (n == 0) {
      noMorePlayers = true;
      return ;
  }
  noMorePlayers = false;
  int index = QRandomGenerator::global()->bounded(0, n); // index random igraca
  for (auto it=players.begin(); it != players.end(); it++){
    if(index==0){
        QJsonObject message = parser->toNewHostMessage();
      //  message[MessageType::TYPE] = MessageType::NEW_HOST;
        it.value()->send(message);
        host = it.key();
      //  std::cout << " new random host " << host.toStdString() << std::endl;
        break;
      }
    index--;
    }
}

void Room::gameOver(Thread* t)
{
  QJsonObject message = parser->toGameOverMessage();
//  message[MessageType::TYPE] = MessageType::GAME_OVER;
  broadcastMessage(message, t);
  gameIsStarted = false;
}


void Room::joinClient(QString username, Thread* thread){

    bool check = usernameIsTaken(username);

    QJsonObject message;

    if(check){
        QString msg = "";
        message = parser->toJoinRoomMessage(msg);

       // message[MessageType::TYPE] = QString(MessageType::JOIN_ROOM);
        thread->send(message);
        return;
    }

    else{

        // javimo ostalima da se prikljucio
        QJsonObject m = parser->toUserJoinedMessage(username);
        broadcastMessage(m, thread);

        // javimo igracu da se prikljucio
        players.insert(username, thread);
        message = parser->toJoinRoomMessage(name);
        thread->send(message);

        // javimo igracu da je igra vec u toku
        if (gameIsStarted){
          QJsonObject gameIsOn = parser->toStartMessage();
          thread->send(gameIsOn);
        }

        //ako je on prvi igrac, onda je host
        if(players.size() == 1){
            QJsonObject message = parser->toNewHostMessage();
            host = username;
            thread->send(message);
        }

        //if there is 2 or more players, start game
        if(players.size() >= 2 and !gameIsStarted)
            start();

        return;
    }
}

void Room::start()
{
    QJsonObject message = parser->toStartMessage();
   //message[MessageType::TYPE] = MessageType::START;

    QMapIterator<QString, Thread*> i(players);
    while (i.hasNext()) {
         i.next();
         i.value()->send(message);
    }

    gameIsStarted = true;

}

void Room::broadcastMessage(const QJsonObject &message, Thread* t) {
    for (auto i=players.begin(); i!=players.end(); i++) {
          i.value()->send(message);
    }

    QString type = message.value(MessageType::TYPE).toString();
    QString word = message.value(MessageType::CONTENT).toString();

    if (gameIsStarted && type.compare(MessageType::TEXT_MESSAGE)==0)
      checkChatWord(word, t);

}

void Room::broadcastCanvas(const QJsonObject &message, Thread *t) {
    for (auto i=players.begin(); i!=players.end(); i++) {
        if (i.value() != t) {
          i.value()->send(message);
        }
    }
}
