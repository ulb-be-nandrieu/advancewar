#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "terrain.h"
#include "player.h"
#include "nombre.h"
#include "cursor.h"
#include "game.h"
#include <QtNetwork>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadimage();
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent *event);


public slots:
    void turn();
    void capt();
    void onNewConnection();
    void onConnected();
    void onDisconnected();
    void onData();



private:
    Game* g = nullptr;
    QPixmap image[126];
    QPixmap imageorange[11];
    QPixmap imageblue[11];
    Cursor point = Cursor(0,0);

    Ui::MainWindow *ui;
    quint32 currentSize = 0;
    bool isConfigured = false;
    void sendJson(QJsonObject obj);

    bool reseau;
    bool myTurn = false;

    QTcpServer* server = nullptr;
    QTcpSocket* other = nullptr;

};


#endif // MAINWINDOW_H
