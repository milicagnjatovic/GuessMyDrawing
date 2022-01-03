#include "settings.h"
#include "ui_settings.h"
#include "game.h"
#include "mainwindow.h"
#include <iostream>

Settings::Settings(Game* game, Client* client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings),
    client(client),
    game(game)
{
    ui->setupUi(this);

    connect(ui->pbSave, &QPushButton::clicked, this, &Settings::SaveClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Settings::BackClicked);
    connect(ui->leUsername, &QLineEdit::textChanged, this,  &Settings::leUsername_textChanged);
    connect(ui->lnRoomName, &QLineEdit::textChanged, this, &Settings::lnRoomName_textChanged);
    connect(ui->rBtn60, &QRadioButton::clicked, this, &Settings::timerDuration60_clicked);
    connect(ui->rBtn90, &QRadioButton::clicked, this, &Settings::timerDuration90_clicked);
    connect(ui->rBtn120, &QRadioButton::clicked, this, &Settings::timerDuration120_clicked);
    connect(client, &Client::errorConnecting, this, &Settings::showPopUp);


    disableInputs();

}

Settings::~Settings()
{
    delete ui;
}

void Settings::SaveClicked()
{
    hide();
    QWidget *parent = this->parentWidget();
    parent->hide();
    username = ui->leUsername->text();
    roomName = ui->lnRoomName->text();

    game->setWindowTitle(roomName);
    sendSettingsToCLient(username, roomName, duration);

    disableInputs();
}

void Settings::BackClicked(){
    hide();

    QWidget *parent = this->parentWidget();
    parent->show();
}

void Settings::timerDuration60_clicked()
{
    duration = 60;
    ui->leUsername->setDisabled(false);

}

void Settings::timerDuration90_clicked()
{
    duration = 90;
    ui->leUsername->setDisabled(false);

}

void Settings::timerDuration120_clicked()
{
    duration = 120;
    ui->leUsername->setDisabled(false);

}


void Settings::sendSettingsToCLient(QString username, QString roomName, int duration){
    client->createRoom(username, roomName, duration);
}




void Settings::leUsername_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

    ui->pbSave->setDisabled(false);

}


void Settings::lnRoomName_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

    ui->rBtn60->setDisabled(false);
    ui->rBtn90->setDisabled(false);
    ui->rBtn120->setDisabled(false);
}

void Settings::showPopUp()
{
    hide();
}

void Settings::disableInputs()
{
    ui->pbSave->setDisabled(true);
    ui->leUsername->setDisabled(true);
    ui->rBtn60->setDisabled(true);
    ui->rBtn90->setDisabled(true);
    ui->rBtn120->setDisabled(true);
    ui->leUsername->setText("");
    ui->lnRoomName->setText("");

}

