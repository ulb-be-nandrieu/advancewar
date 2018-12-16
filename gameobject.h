#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


class Gameobject {
protected:
    int posX =0;
    int posY=0;
public:
    Gameobject(int x, int y);
    int getposX();
    int getposY();
    void setposX(int x);
    void setposY(int y);
};


#endif // GAMEOBJECT_H
