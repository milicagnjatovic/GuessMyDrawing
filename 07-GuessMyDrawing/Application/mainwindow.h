#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "client.h"
#include "existingrooms.h"
#include "game.h"
#include "settings.h"
#include "chooseword.h"
#include "popup.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QString username, QWidget *parent = nullptr);
  ~MainWindow();
  void closeEvent(QCloseEvent* event) override;
public slots:
  void JoinGameClicked();
  void CreateNewGameClicked();
  void gameWindowClosed();
  void showPopUp();
public:
  void attemptConnection(qint16 port);
private:
  Ui::MainWindow *ui;
  ExistingRooms* existingRooms = nullptr;
  Settings *settings = nullptr;
  Client *chatClient;
  Game *game;
  ChooseWord *chooseWord;
  PopUp *popUpWindow;

};
#endif // MAINWINDOW_H
