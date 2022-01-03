#include "game.h"
#include "ui_game.h"
#include "canvas.h"
#include "client.h"
#include<iostream>


Game::Game(Client* client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game),
    _canvas(new Canvas(this)),
    client(client),
    timerCanvas(new QTimer(this)),
    mChatModel(new QStandardItemModel(this))
{
    ui->setupUi(this);
    _canvas->resize(600, 600); // showing canvas

    // disabling drawing on canvas, clearing canvas and modifying the pen
    _canvas->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->pbClearDrawing->setEnabled(false);
    ui->pbDecPenWidth->setEnabled(false);
    ui->pbIncPenWidth->setEnabled(false);
    ui->cbPenColor->setEnabled(false);

    // CANVAS clearing canvas, modifying the pen
    connect(ui->pbClearDrawing, &QPushButton::clicked, this, &Game::onClearDrawing);
    connect(ui->cbPenColor, &QComboBox::currentTextChanged, this, &Game::onChangePenColor);
    connect(ui->pbIncPenWidth, &QPushButton::clicked, this, &Game::onIncPenWidth);
    connect(ui->pbDecPenWidth, &QPushButton::clicked, this, &Game::onDecPenWidth);

    // FOR CHAT
    mChatModel->insertColumn(0);
    ui->listView->setModel(mChatModel);

    connect(client, &Client::messageReceived, this, &Game::messageRecieved);
    connect(client, &Client::userJoined, this, &Game::userJoined);
    connect(client, &Client::userLeft, this, &Game::userLeft);
    connect(client, &Client::youAreNewHost, this, &Game::You_Are_Host);
    connect(client, &Client::startGame, this, &Game::Start_Game);
    connect(client, &Client::gameOver, this, &Game::Game_Over);
    connect(client, &Client::errorConnecting, this, &Game::showPopUp);


    connect(ui->btnSend, &QPushButton::clicked, this, &Game::sendMessage);

    connect(timerCanvas, &QTimer::timeout, this, &Game::sendCanvasMessage);


    connect(ui->leInput, &QLineEdit::returnPressed, this, &Game::sendMessage); // send on enter

    // CANVAS
    connect(client, &Client::canvasReceived, this, &Game::onLoadCanvas); // send on enter
    timerCanvas->start(50);
}
Game::~Game()
{
    delete mChatModel;
    delete _canvas;
    delete ui;
}


Canvas *Game::getCanvas() const
{
    return _canvas;
}

void Game::onClearDrawing()
{
    _canvas->clearImage();
}

void Game::onChangePenColor()
{
    QColor color = Qt::black;
    if (ui->cbPenColor->currentText().compare("Blue") == 0) {
        color = Qt::blue;
    }
    if (ui->cbPenColor->currentText().compare("Red") == 0) {
        color = Qt::red;
    }
    if (ui->cbPenColor->currentText().compare("Green") == 0) {
        color = Qt::green;
    }
    if (ui->cbPenColor->currentText().compare("Yellow") == 0) {
        color = Qt::yellow;
    }
    if (ui->cbPenColor->currentText().compare("Magenta") == 0) {
        color = Qt::magenta;
    }
    if (ui->cbPenColor->currentText().compare("White") == 0) {
        color = Qt::white;
    }
    _canvas->setPenColor(color);
}

void Game::onIncPenWidth()
{
    int currPenWidth = _canvas->penWidth();
    _canvas->setPenWidth(currPenWidth+1);
}

void Game::onDecPenWidth()
{
    int currPenWidth = _canvas->penWidth();
    _canvas->setPenWidth(currPenWidth-1);
}

void Game::onLoadCanvas(QString s){
    _canvas->loadFromSnapshot(s);
}

//void Game::onLoadImage(QByteArray b)
//{
// // std::cout << "LOADING" <<std::endl;
////  std::cout << b.toStdString() << std::endl;
//    _canvas->loadFromSnapshot(b);
//}

int Game::getDuration() const
{
    return duration;
}

void Game::setDuration(int newDuration)
{
  duration = newDuration;
}


void Game::closeEvent(QCloseEvent *event)
{
  Q_UNUSED(event);

  std::cout << "Game close event!" << std::endl;
  mChatModel->removeRows(0, mChatModel->rowCount());

    this->hide();
    QWidget *parent = this->parentWidget();

    parent->show();
    client->leaveRoom();
}

void Game::You_Are_Host()
{
    // host cannot type in chat
    ui->leInput->setDisabled(true);

    // only host can draw, clear his drawing or modify his pen
    enableCanvas(true);

    emit IAmHost();
}

void Game::Start_Game()
{
  std::cout << "START" <<std::endl;
  _canvas->clearImage();
  if (client->isHost()) {
    ui->leInput->setDisabled(true);

    // only host can draw, clear his drawing or modify his pen
    enableCanvas(true);
  }
  else {
    ui->leInput->setDisabled(false);

    // player is not the host, so he cannot draw, clearDrawing or modify his pen
    enableCanvas(false);
  }
}

void Game::Game_Over()
{

   ui->leInput->setDisabled(true);


}

void Game::showPopUp()
{
    hide();
}

void Game::enableCanvas(const bool isHost)
{
    _canvas->setAttribute(Qt::WA_TransparentForMouseEvents, !isHost);
    ui->pbClearDrawing->setEnabled(isHost);
    ui->pbDecPenWidth->setEnabled(isHost);
    ui->pbIncPenWidth->setEnabled(isHost);
    ui->cbPenColor->setEnabled(isHost);
}

// FOR CHAT
void Game::sendMessage()
{
  client->send(ui->leInput->text());

//  int newRow = mChatModel->rowCount();
//  mChatModel->insertRow(newRow);
//  mChatModel->setData(mChatModel->index(newRow,0), ui->leInput->text());
//  mChatModel->setData(mChatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
//  ui->listView->scrollToBottom();
  ui->leInput->setText("");
}

void Game::sendCanvasMessage() {
    if (client->isHost()){
//        QByteArray b;
//        _canvas->takeSnapshot(b);
//        client->sendCanvas(b);
        QString s = _canvas->takeSnapshot();
        client->sendCanvas(s);
    }
}

void Game::messageRecieved(const QString &sender, const QString &text)
{
//  std::cout << sender.toStdString() << " " << text.toStdString() << std::endl;
  int newRow = mChatModel->rowCount();
  mChatModel->insertRow(newRow);
  mChatModel->setData(mChatModel->index(newRow,0), sender + " : " + text);
  mChatModel->setData(mChatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
  ui->listView->scrollToBottom();
}

void Game::userJoined(const QString &username)
{
  int newRow = mChatModel->rowCount();
  mChatModel->insertRow(newRow);
  mChatModel->setData(mChatModel->index(newRow,0), username + " joined");
  mChatModel->setData(mChatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
  ui->listView->scrollToBottom();
//  show();
}

void Game::userLeft(const QString &username)
{
  int newRow = mChatModel->rowCount();
  mChatModel->insertRow(newRow);
  mChatModel->setData(mChatModel->index(newRow,0), username + " left");
  mChatModel->setData(mChatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
  ui->listView->scrollToBottom();
}


