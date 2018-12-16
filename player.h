#ifndef PLAYER_H
#define PLAYER_H
#include "gameobject.h"
#include "batiment.h"
#include <vector>
#include <iostream>
#include "unit.h"
using namespace std;

class Player {
    int money;
    vector <Unit*> unitlist;

public:
    explicit Player(int m = 0);
    void earnmoney(int n);
    void buyUnit(int t,int x, int y);
    void resetUnit();
    void resetselected();
    int getmoney();
    void fusion(int u1,int u2);
    void deleteunit(int i);

    vector <Unit*> getunitlist();

    ~Player();

};


#endif // PLAYER_H
