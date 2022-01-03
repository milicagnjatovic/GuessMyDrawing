#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "game.h"
#include "client.h"
#include "client.h"
#include "chooseword.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(Game* game, Client* client, QWidget *parent = nullptr);
    ~Settings();

    void sendSettingsToCLient(QString username, QString roomName, int duration);
    void disableInputs();


signals:
    void signalThatGameWindowIsClosed();

private slots:
    void SaveClicked();
    void BackClicked();

    void timerDuration60_clicked();
    void timerDuration90_clicked();
    void timerDuration120_clicked();

    void leUsername_textChanged(const QString &arg1);
    void lnRoomName_textChanged(const QString &arg1);
    void showPopUp();

private:
    Ui::Settings *ui;
    Client *client;
    Game *game;
    int duration;
    QString roomName;
    QString username;



};

#endif // SETTINGS_H
