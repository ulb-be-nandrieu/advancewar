#ifndef BATIMENT_H
#define BATIMENT_H
#include "terrain.h"

class Batiment: public Terrain
{
    int camp;
    int capture = 20;

public:
    Batiment(int x, int y, int t,int c);
    void setcamp(int c);
    int getcamp();
    void captured(int c);
    void setcapture(int c);
    int getcapture();
};

#endif // BATIMENT_H
