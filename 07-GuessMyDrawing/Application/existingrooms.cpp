 #include "existingrooms.h"
#include "ui_existingrooms.h"
#include <iostream>

ExistingRooms::ExistingRooms(Game* game, Client* client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExistingRooms),
    client(client),
    game(game)
{
    ui->setupUi(this);
    connect(client, &Client::roomList, this, &ExistingRooms::getActiveRooms);
    connect(ui->leUsername, &QLineEdit::textEdited, this, &ExistingRooms::leUsername_textEdited);

    connect(ui->listOfRooms, &QListWidget::itemClicked, this, &ExistingRooms::listOfRooms_itemClicked);
    connect(ui->pbJoin, &QPushButton::clicked, this, &ExistingRooms::pbJoin_clicked);
    connect(client, &Client::joinedRoom, this, &ExistingRooms::JoinedRoom);
    connect(client, &Client::errorConnecting, this, &ExistingRooms::showPopUp);


//    client->getRooms();

    ui->pbJoin->setDisabled(true);
    ui->listOfRooms->setDisabled(true);


}
ExistingRooms::~ExistingRooms()
{
  std::cout << "Existing rooms destrucotr" << std::endl;
    delete ui;
}

void ExistingRooms::listOfRooms_itemClicked(QListWidgetItem *item)
{
    Q_UNUSED(item);

    ui->pbJoin->setDisabled(false);
    selectedRoom = ui->listOfRooms->selectedItems()[0]->text();
}

void ExistingRooms::getActiveRooms(const QVector<QString> *r)
{
    activeRooms = r;

    ui->listOfRooms->clear();
    for (int i=0; i< activeRooms->size() ; ++i) {
       ui->listOfRooms->addItem(activeRooms->at(i));
    }
    // TODO check
    delete r;

}



void ExistingRooms::pbJoin_clicked()
{

//    hide();
//    QWidget *parent = this->parentWidget();
//    parent->hide();
   // std::cout << username.toStdString() << std::endl;

   // hide();
    client->joinRoom(username, selectedRoom);
    game->setWindowTitle(selectedRoom);
    ui->pbJoin->setDisabled(true);
}

void ExistingRooms::JoinedRoom(bool p)
{
  //  std::cout << "Ovde je p" << p << std::endl;
    if(p){
        hide();
        QWidget *parent = this->parentWidget();
        parent->hide();
        game->show();
    }
    else {
       ui->leUsername->setText("Please enter another name");
    }


}


void ExistingRooms::leUsername_textEdited(const QString &arg1)
{
    Q_UNUSED(arg1);

    username = ui->leUsername->text();

    ui->listOfRooms->setDisabled(false);
}

void ExistingRooms::showPopUp()
{
    hide();
}



