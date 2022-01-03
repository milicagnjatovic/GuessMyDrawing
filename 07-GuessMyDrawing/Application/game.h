#ifndef GAME_H
#define GAME_H

#include "canvas.h"
#include "client.h"
#include <QDialog>
#include <QCloseEvent>
#include <QMainWindow>
#include <QWidget>
#include <QStandardItemModel>
#include <QTimer>

namespace Ui {
class Game;
}

class Game : public QDialog
{
    Q_OBJECT

public:
    explicit Game(Client* client, QWidget *parent = nullptr);
    ~Game();

    Canvas *getCanvas() const;

    int getDuration() const;
    void setDuration(int newDuration);
    void closeEvent( QCloseEvent* event ) override;

private slots:
    void sendMessage();
    void sendCanvasMessage();
    void messageRecieved(const QString &sender, const QString &text);
    void userLeft(const QString &username);
    void userJoined(const QString &username);
    void You_Are_Host();
    void Start_Game();
    void Game_Over();
    void showPopUp();

public slots:
    void onClearDrawing();
    void onChangePenColor();
    void onIncPenWidth();
    void onDecPenWidth();
//    void onLoadImage(QByteArray b);
    void onLoadCanvas(QString s);

signals:
    void IAmHost();
    void LeaveClicked();

private:
    Ui::Game *ui;
    Canvas *_canvas;

    int duration;
    QString chosenWord;
    Client *client;
    QString username;

    QTimer* timerCanvas;
    void enableCanvas(const bool isHost);

    // chat
    QStandardItemModel *mChatModel;
};

#endif // GAME_H
