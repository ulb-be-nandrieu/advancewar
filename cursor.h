#ifndef CURSOR_H
#define CURSOR_H
#include "gameobject.h"

class Cursor : public Gameobject
{
public:
    Cursor(int x, int y);
    void move(int x, int y);
};

#endif // CURSOR_H
