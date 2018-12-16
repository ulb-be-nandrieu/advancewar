#include "head.h"

Terrain::Terrain(int x, int y, int n) : Gameobject (x,y)
{
    num = n;

    if (num == 1){
        type = 0;           // plain
    } else if (num == 2){
        type = 1;           // mountain
    } else if (num == 3){
        type = 2;           // wood
    } else if (num == 4 || num == 5 || num == 7 || num == 8 || num == 9 || num == 10){
        type = 3;           // river
    } else if (num == 15 || num == 16 || num == 18 || num == 19 || num == 20 || num == 21 || num == 22 || num == 23 || num == 24 || num == 25){
        type = 4;           // road
    } else if (num == 26){
        type = 5;           // bridge
    } else if (num == 34 || num == 95 || num == 125){
        type = 6;           // city
    } else if (num == 35 || num == 92 || num == 123){
        type = 7;           // base
    } else if (num == 36 || num == 93 || num == 124){
        type = 8;           // airport
    } else if (num == 29 || num == 30){
        type = 9;           // hoal
    } else if (num == 33){
        type = 10;          // reef
    } else if (num == 101 || num == 102 || num == 104 || num == 106 || num == 107 || num == 108 || num == 109 || num == 110){
        type = 11;          // pipe
    }

    int chart[6][12];

    //1000 = pas de déplacement possible

    chart[0][0] = 1;
    chart[1][0] = 1;
    chart[2][0] = 1;
    chart[3][0] = 1;
    chart[4][0] = 2;
    chart[5][0] = 1;

    chart[0][1] = 4;
    chart[1][1] = 2;
    chart[2][1] = 1;
    chart[3][1] = 1000;
    chart[4][1] = 1000;
    chart[5][1] = 1;

    chart[0][2] = 2;
    chart[1][2] = 1;
    chart[2][2] = 1;
    chart[3][2] = 2;
    chart[4][2] = 3;
    chart[5][2] = 1;

    chart[0][3] = 0;
    chart[1][3] = 2;
    chart[2][3] = 1;
    chart[3][3] = 1000;
    chart[4][3] = 1000;
    chart[5][3] = 1;

    chart[0][4] = 0;
    chart[1][4] = 1;
    chart[2][4] = 1;
    chart[3][4] = 1;
    chart[4][4] = 1;
    chart[5][4] = 1;

    chart[0][5] = 0;
    chart[1][5] = 1;
    chart[2][5] = 1;
    chart[3][5] = 1;
    chart[4][5] = 1;
    chart[5][5] = 1;

    chart[0][6] = 3;
    chart[1][6] = 1;
    chart[2][6] = 1;
    chart[3][6] = 1;
    chart[4][6] = 1;
    chart[5][6] = 1;

    chart[0][7] = 3;
    chart[1][7] = 1;
    chart[2][7] = 1;
    chart[3][7] = 1;
    chart[4][7] = 1;
    chart[5][7] = 1;

    chart[0][8] = 3;
    chart[1][8] = 1;
    chart[2][8] = 1;
    chart[3][8] = 1;
    chart[4][8] = 1;
    chart[5][8] = 1;

    chart[0][9] = 0;
    chart[1][9] = 1;
    chart[2][9] = 1;
    chart[3][9] = 1;
    chart[4][9] = 1;
    chart[5][9] = 1;

    chart[0][10] = 1;
    chart[1][10] = 1000;
    chart[2][10] = 1000;
    chart[3][10] = 1000;
    chart[4][10] = 1000;
    chart[5][10] = 1;

    chart[0][11] = 0;
    chart[1][11] = 1000;
    chart[2][11] = 1000;
    chart[3][11] = 1000;
    chart[4][11] = 1000;
    chart[5][11] = 1000;



    def = chart[0][type];
    mt[0] = chart[1][type]; // F
    mt[1] = chart[2][type]; // B
    mt[2] = chart[3][type]; // W
    mt[3] = chart[4][type]; // T
    mt[4] = chart[5][type]; // A
}

int Terrain::gettype(){
    return this->type;
}

int Terrain::getnum(){
    return this->num;
}

int Terrain::getdef(){
    return this->def;
}

void Terrain::settype(int t){
    this->type = t;
}

void Terrain::setnum(int n){
    this->num = n;
}

int Terrain::getmt(int i){
    return this->mt[i];
}
