#ifndef NODES_H
#define NODES_H
#include "terrain.h"
#include <vector>

class nodes
{
    int posX;
    int posY;
    int mp;
    bool waiting = false;
    bool saved = false;
public:

    nodes(int x, int y, int mp, bool waiting = false, bool saved = false);
    int getCasemp(int x, int y, int type, std::vector <Terrain*> ter);
    int getposX();
    int getposY();
    int getmp();
    bool getwaiting();
    bool getsaved();
    void setwaiting(bool x);
    void setsaved(bool y);
    void setmp(int i);
};

#endif // NODES_H
