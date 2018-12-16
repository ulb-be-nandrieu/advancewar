#ifndef UNIT_H
#define UNIT_H

#include "gameobject.h"

class Unit: public Gameobject {

    int type;
    int movetype;
    int mpmax;
    int mp = 0;
    int cost;
    int pv = 10;
    bool att = false;
    bool selected = false;

public :

    Unit(int x, int y, int t);
    void move(int x, int y, int c);
    bool attacked(int d);
    void addpv(int v);


    int gettype();
    int getmovetype();
    int getmp();
    int getmpmax();
    int getpv();
    bool getatt();
    bool getselected();
    int getcost();

    void setmp(int m);
    void setatt(bool a);
    void setselected(bool a);
    void setPos(int x,int y);

};

#endif // UNIT_H
