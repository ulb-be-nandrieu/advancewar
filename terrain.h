#ifndef TERRAIN_H
#define TERRAIN_H
#include "gameobject.h"

class Terrain: public Gameobject
{
    int num;
    int type;
    int def;
    int mt[5];

public:
    Terrain(int x, int y, int n);
    int gettype();
    int getnum();
    int getdef();
    void settype(int t);
    void setnum(int n);
    int getmt(int i);

};

#endif // TERRAIN_H
