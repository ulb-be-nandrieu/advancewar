#include "head.h"

Gameobject::Gameobject(int x, int y)
{
    posX = x;
    posY = y;
}

int Gameobject::getposX(){
    return this->posX;
}
int Gameobject::getposY(){
    return this->posY;
}
void Gameobject::setposX(int x){
    this->posX = x;
}
void Gameobject::setposY(int y){
    this->posY = y;
}
