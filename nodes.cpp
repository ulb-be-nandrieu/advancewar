#include "nodes.h"
#include "head.h"


nodes::nodes(int x, int y, int mp, bool waiting, bool saved)
{
    this->posX=x;
    this->posY=y;
    this->mp=mp;
    this->waiting=waiting;
    this->saved=saved;
}

int nodes::getCasemp(int x, int y, int type, vector <Terrain*> ter){
    for (unsigned int i=0; i<ter.size(); i++){
        if (ter[i]->getposX()==x && ter[i]->getposY()==y){
            int n = ter[i]->getmt(type);
            return n;
        }
    }
}

int nodes::getposX()
{
    return this->posX;
}

int nodes::getposY()
{
    return this->posY;
}

int nodes::getmp()
{
    return this->mp;
}

bool nodes::getwaiting()
{
    return this->waiting;
}

void nodes::setwaiting(bool w)
{
    this->waiting=w;
}

bool nodes::getsaved()
{
    return this->saved;
}

void nodes::setsaved(bool s)
{
    this->saved=s;
}

void nodes::setmp(int i){
    this->mp=i;
}
