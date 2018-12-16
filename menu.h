#ifndef MENU_H
#define MENU_H

#include<QDialog>
#include<QWidget>
#include "player.h"
#include "game.h"

class Menu : public QDialog
{
    Q_OBJECT

public:
    Menu(QWidget *parent, Game* game, int x, int y);
    Game* game;
    int x;
    int y;

public slots:
    void infantry();
    void mech();
    void recon();
    void antiair();
    void tank();
    void mdtank();
    void megatank();
    void neotank();
    void bcopter();
    void fighter();
    void bomber();

};

#endif // MENU_H
