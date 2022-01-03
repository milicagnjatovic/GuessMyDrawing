#ifndef POPUP_H
#define POPUP_H

#include <QDialog>
#include "client.h"

namespace Ui {
class PopUp;
}

class PopUp : public QDialog
{
    Q_OBJECT

public:
    explicit PopUp(Client *client, QWidget *parent = nullptr);
    ~PopUp();

private slots:
    void reconnect();

private:
    Ui::PopUp *ui;
    Client *client;
};

#endif // POPUP_H
