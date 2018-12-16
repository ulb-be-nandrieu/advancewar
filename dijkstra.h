#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include "nodes.h"
#include "unit.h"
#include "game.h"
#include "terrain.h"

class dijkstra
{
    std::vector<nodes*> listNodes;
public:
    std::vector<nodes*> getlistNodes();
    dijkstra(Game* g, int unit);
    int getMp(int x, int y, int type, std::vector <Terrain*> ter);
    int cost (int x, int y);
};

#endif // DIJKSTRA_H
