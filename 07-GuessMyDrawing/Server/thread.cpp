#include "thread.h"
#include <iostream>


Thread::Thread(qintptr ID, QObject *parent) :
    QObject(parent),
    socketMessage(new QTcpSocket(this)) {
    this->socketDescriptor = ID;
    if (!socketMessage->setSocketDescriptor(this->socketDescriptor)) {
        std::cerr << socketMessage->error();
        return;
    }
    connect(socketMessage, SIGNAL(readyRead()), this, SLOT(onMessageReadyRead()), Qt::DirectConnection);
    connect(socketMessage, SIGNAL(disconnected()), this, SLOT(onDisconnectedMessage()), Qt::DirectConnection);

    room_name = "";
    std::cout << socketDescriptor << " Client connected!" << std::endl;
}

void Thread::disconnect() {
    socketMessage->deleteLater();
}

Thread::~Thread() {
    socketMessage->deleteLater();
}

void Thread::send(QJsonObject message)
{
  auto msg = QJsonDocument(message).toJson(QJsonDocument::Compact);
  socketMessage->write(msg);
  socketMessage->flush();
}

void Thread::onMessageReadyRead() {
    QByteArray data = socketMessage->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    emit messageReceived(doc.object(), this);
}

void Thread::onDisconnectedMessage() {
    std::cout << socketDescriptor << " disconnected! " << std::endl;
    socketMessage->deleteLater();
}

quintptr Thread::getSocketDescriptor() {
    return socketDescriptor;
}

void Thread::setRoomName(QString name) {
    this->room_name = name;
}

QString Thread::getRoomName() {
    return room_name;
}

