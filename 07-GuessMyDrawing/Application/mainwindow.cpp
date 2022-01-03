#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "existingrooms.h"
#include "settings.h"
#include <QHostAddress>

MainWindow::MainWindow(QString username, QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {
  chatClient = new Client(username, this);
  attemptConnection(1234);

  ui->setupUi(this);
  connect(ui->pbJoinGame, &QPushButton::clicked, this, &MainWindow::JoinGameClicked);
  connect(ui->pbCreateNewGame, &QPushButton::clicked, this, &MainWindow::CreateNewGameClicked);
  connect(chatClient, &Client::errorConnecting, this, &MainWindow::showPopUp);

  game = new Game(chatClient, this);
  chooseWord = new ChooseWord(game, chatClient, this);
  popUpWindow = new PopUp(chatClient, this);
}

MainWindow::~MainWindow() {
    delete ui;
    delete chatClient;
    delete game;
    delete chooseWord;
    delete popUpWindow;
    if (!existingRooms) {
        delete existingRooms;
    }
    if (!settings) {
        delete settings;
    }
}

void MainWindow::attemptConnection(qint16 port) {
  // Update
  // Possibly static adres and port from server?
  chatClient->connectToServer(QHostAddress::LocalHost, port);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    Q_UNUSED(event);

    std::cout << "MainWindow close event!" << std::endl;
    exit(0);
}

void MainWindow::JoinGameClicked() {
    chatClient->getRooms();
    if (existingRooms == nullptr)
      existingRooms = new ExistingRooms(game, chatClient, this);
    existingRooms->setModal(true);
    //opening the second window
    existingRooms->exec();
    std::cout << "DONE settings" << std::endl;
}

void MainWindow::CreateNewGameClicked() {
    if (settings==nullptr)
        settings = new Settings(game, chatClient, this);

    settings->disableInputs();
    settings->setModal(true);
 //   settings->show();
    settings->exec();
    std::cout << "DONE settings" << std::endl;
}



void MainWindow::gameWindowClosed() {
}

void MainWindow::showPopUp() {
    hide();
    popUpWindow->show();
}

