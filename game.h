#ifndef GAME_H
#define GAME_H

#include "terrain.h"
#include "batiment.h"
#include "player.h"
#include <QMainWindow>

#include <QtNetwork>

class Game
{
    vector <Terrain*> ter;
    vector <Batiment*> allbat;
    Player* p1;     //orange
    Player* p2;     //blue
    Player* actif;
    Player* inactif;
    QMainWindow* mw;
    int tour = 1;
    bool finish = false;
    bool iaplay;
    int nombreType;

    quint32 currentSize = 0;
    bool isConfigured = false;

    int posX = 100, posY =150;
    void sendJson(QJsonObject obj);

    QTcpServer* server = nullptr;
    QTcpSocket* other = nullptr;

public slots:
    void onNewConnection();
    void onConnected();
    void onDisconnected();
    void onData();


public:
    Game(QMainWindow* mw);
    ~Game();
    vector<string> split(string s, string delimiter);
    void endturn();
    bool isobstacle(int posx, int posy);
    void moveunit(int x, int y, int i);
    void endgame();
    void attaque(int mx,int my, int i);
    void capture();
    int damage(Unit* ua, Unit* ud,int x,int y);
    std::tuple<int,int> pressed(int mx, int my);


    vector <Terrain*> getter();
    vector <Batiment*> getallbat();
    Player* getp1();
    Player* getp2();
    Player* getactif();
    Player* getinactif();
    int gettour();
    bool getfinish();
    int getnombreType();
    void setnombreType(int i);

};


#endif // GAME_H
