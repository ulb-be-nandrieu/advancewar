#ifndef IA_H
#define IA_H

#include "batiment.h"
#include "terrain.h"
#include "player.h"
#include "mainwindow.h"
#include "game.h"

class Ia
{
    Game* game;

public:
    Ia(Game* g);
    void greedy(int i);


};

#endif // IA_H
