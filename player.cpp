#include "head.h"

Player::Player(int m){
    this->money = m;
}

void Player::earnmoney(int n){
    this->money += 1000 * n;
}

void Player::buyUnit(int t,int x, int y){
    Unit* uni = new Unit(x,y,t);
    if (this->money > uni->getcost()){
        this->unitlist.push_back(uni);
        money -= uni->getcost();
    } else {
        delete uni;
    }
}

void Player::resetUnit() {
    unsigned int s = unitlist.size();
    for (unsigned int i = 0; i<s; i++){
        unitlist[i]->setmp(unitlist[i]->getmpmax());
        unitlist[i]->setatt(true);
    }
}

void Player::resetselected(){
    unsigned int s = unitlist.size();
    for (unsigned int i = 0; i<s; i++){
        unitlist[i]->setselected(false);
    }
}

int Player::getmoney(){
    return this->money;
}

void Player::fusion(int u1,int u2){
    if(unitlist[u2]->getpv() < 10 && unitlist[u1]->gettype() == unitlist[u2]->gettype()){
        unitlist[u2]->addpv(unitlist[u1]->getpv());
        deleteunit(u1);
    }
}

void Player::deleteunit(int i){
    unitlist.erase(unitlist.begin()+i);
}

vector<Unit *> Player::getunitlist()
{
    return this->unitlist;
}

Player::~Player()
{
    for (int i=0;i<this->unitlist.size();i++){
        delete this->unitlist[i];
    }
}

