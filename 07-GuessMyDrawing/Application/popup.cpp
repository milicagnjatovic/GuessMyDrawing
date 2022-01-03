#include "popup.h"
#include "ui_popup.h"

PopUp::PopUp(Client *client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PopUp),
    client(client)
{
    ui->setupUi(this);
    hide();

    connect(ui->pbTryAgain, &QPushButton::clicked, this, &PopUp::reconnect);
}

PopUp::~PopUp()
{
    delete ui;
}

void PopUp::reconnect()
{
    client->reconnect();
    hide();

    QWidget *parent = this->parentWidget();
    parent->show();
}
