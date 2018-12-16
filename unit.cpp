#include "head.h"

Unit::Unit(int x, int y, int t) : Gameobject(x,y)
{
    type = t;

    int units[3][11];

    // 0: infantry
    units[0][0] = 3;
    units[1][0] = 0;    // "F"
    units[2][0] = 1000;

    // 1: mech
    units[0][1] = 2;
    units[1][1] = 1;    // "B"
    units[2][1] = 3000;

    // 2: recon
    units[0][2] = 8;
    units[1][2] = 2;    // "W"
    units[2][2] = 4000;

    // 3: anti-air
    units[0][3] = 6;
    units[1][3] = 3;    // "T"
    units[2][3] = 8000;

    // 4: tank
    units[0][4] = 6;
    units[1][4] = 3;    // "T"
    units[2][4] = 7000;

    // 5: md.tank
    units[0][5] = 5;
    units[1][5] = 3;    // "T"
    units[2][5] = 16000;

    // 6: mega tank
    units[0][6] = 4;
    units[1][6] = 3;    // "T"
    units[2][6] = 28000;

    // 7: neotank
    units[0][7] = 6;
    units[1][7] = 3;    // "T"
    units[2][7] = 22000;

    // 8: b-copter
    units[0][8] = 6;
    units[1][8] = 4;    // "A"
    units[2][8] = 9000;

    // 9: fighter
    units[0][9] = 9;
    units[1][9] = 4;    // "A"
    units[2][9] = 20000;

    // 10: bomber
    units[0][10] = 7;
    units[1][10] = 4;    // "A"
    units[2][10] = 22000;


    this->mpmax = units[0][t];
    this->movetype = units[1][t];
    this->cost = units[2][t];
}


void Unit::move(int x, int y, int d){
    if (x < 0 || x > SIZEMAP_X || y < 0 || y > SIZEMAP_Y){
        cout<<"hors de la map"<<endl;
    } else {
        posX = x;
        posY = y;
        mp -= d;
    }
}

bool Unit::attacked(int d){
    this->pv -=d;
    if (pv <= 0){
        return false;
    } else {
        return true;
    }
}
void Unit::addpv(int v){
    this->pv += v;
    if (pv > 10){
        pv = 10;
    }
}

int Unit::gettype(){
    return this->type;
}
int Unit::getmovetype(){
    return this->movetype;
}
int Unit::getmp(){
    return this->mp;
}
int Unit::getmpmax(){
    return this->mpmax;
}
int Unit::getpv(){
    return this->pv;
}
bool Unit::getatt(){
    return this->att;
}
bool Unit::getselected(){
    return this->selected;
}
int Unit::getcost(){
    return this->cost;
}
void Unit::setmp(int m){
    this->mp = m;
}
void Unit::setatt(bool a){
    this->att = a;
}
void Unit::setselected(bool a){
    this->selected = a;
}

