#ifndef EXISTINGROOMS_H
#define EXISTINGROOMS_H

#include <QDialog>
#include "client.h"
#include <QListWidgetItem>
#include "game.h"
#include "chooseword.h"

namespace Ui {
class ExistingRooms;
}

class ExistingRooms : public QDialog
{
    Q_OBJECT

public:
    explicit ExistingRooms(Game* game, Client* client, QWidget *parent = nullptr);
    ~ExistingRooms();

private slots:
    void listOfRooms_itemClicked(QListWidgetItem *item);
    void getActiveRooms(const QVector<QString>* r);
    void pbJoin_clicked();
    void JoinedRoom(bool p);

    void leUsername_textEdited(const QString &arg1);
    void showPopUp();

private:
    Ui::ExistingRooms *ui;
    Client *client;
    const QVector<QString>* activeRooms;
    QString username = "";
    QString selectedRoom;
    Game* game;
  //  ChooseWord *chooseWord;

};

#endif // EXISTINGROOMS_H
