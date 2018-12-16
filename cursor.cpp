#include "head.h"

Cursor::Cursor(int x, int y) : Gameobject (x,y)
{

}

void Cursor::move(int x, int y){
    if (x < 0 || x > SIZEMAP_X-1 || y < 0 || y > SIZEMAP_Y-1){
        cout<<"hors de la map"<<endl;
    } else {
        posX = x;
        posY = y;
    }
}
