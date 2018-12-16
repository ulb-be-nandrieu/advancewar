#include "head.h"

Game::Game(QMainWindow* mw)
{
    this->p1 = new Player(10000);
    this->p2 = new Player(10000);
    this->actif = p1;
    this->inactif = p2;
    this->mw = mw;

    vector <string> smap = split(mapl,",");
    vector<int> nummap;
    for (unsigned int i=0; i<smap.size();i++){
        nummap.push_back(std::stoi(smap[i]));
    }

    for (unsigned int i=0; i<nummap.size(); i++){
        this->ter.push_back(new Terrain(i%SIZEMAP_X,i/SIZEMAP_X,nummap[i]));
        if (nummap[i]==34 or nummap[i]==35 or nummap[i]==36){       //neutre
            Batiment *bat = static_cast<Batiment*>(ter[i]);
            bat->setcamp(0);
            allbat.push_back(bat);
        } else if (nummap[i]==92 or nummap[i]==93 or nummap[i]==95){    // blue
            Batiment *bat = static_cast<Batiment*>(ter[i]);
            bat->setcamp(1);
            allbat.push_back(bat);
        } else if (nummap[i]==123 or nummap[i]==124 or nummap[i]==125){     //orange
            Batiment *bat = static_cast<Batiment*>(ter[i]);
            bat->setcamp(2);
            allbat.push_back(bat);
        }
    }
    for (unsigned int j=0; j<allbat.size(); j++){
        allbat[j]->setcapture(20);
    }

    // test endgame
//    Unit* u1 = new Unit(16,2,0);
//    p1->unitlist.push_back(u1);
//    Unit* u2 = new Unit(15,3,0);
//    p1->unitlist.push_back(u2);
//    Unit* u3 = new Unit(16,4,0);
//    p1->unitlist.push_back(u3);

      iaplay = true; //true pour activer l'ia

      if(iaplay){
//          Unit* u1 = new Unit(16,2,0);
//          p2->getunitlist().push_back(u1);
          //Unit* u2 = new Unit(15,3,0);
          //p2->unitlist.push_back(u2);
          //Unit* u3 = new Unit(16,4,0);
          //p2->unitlist.push_back(u3);

          p2->buyUnit(0,16,2); //u1

//          p2->buyUnit(0,16,4); //u3

//          p2->buyUnit(0,15,3); //u2



       }
}

Game::~Game(){
    delete p1;
    delete p2;
    for (int i=0;i<ter.size();i++){
        delete ter[i];
    }
}

vector<string> Game::split(string s, string delimiter){
    vector<string> list;
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    list.push_back(s);
    return list;
}

void Game::endturn(){
    actif->resetselected();
    int n = 0;
    unsigned int l = allbat.size();
    if (actif == p1){
        actif = p2;
        inactif = p1;
        for (unsigned int i = 0; i<l; i++){
            if (allbat[i]->getcamp() == 2){
                n++;
            }
        }
    } else {
        actif = p1;
        inactif = p2;
        for (unsigned int i = 0; i<l; i++){
            if (allbat[i]->getcamp() == 1){
                n++;
            }
        }
    }
    actif->earnmoney(n);
    actif->resetUnit();
    tour ++;

    if (iaplay){
        cout<<"tour: "<<tour<<endl;
        if (actif == p2){
            Ia* ia = new Ia(this);
            for (int i = 0; i<actif->getunitlist().size(); i++){
               ia->greedy(i);
            }
            delete ia;
            mw->repaint();
            endturn();

        } else {
            if(tour<500 && !finish){
               endturn();
            }
        }
    }
}


bool Game::isobstacle(int posx, int posy){
    bool b = false;
    unsigned int l = p1->getunitlist().size();
    for (unsigned int i = 0; i<l; i++){
        int x = p1->getunitlist()[i]->getposX();
        int y = p1->getunitlist()[i]->getposY();
        if (x == posx && y == posy){
            b = true;
            break;
        }
    }
    unsigned int l2 = p2->getunitlist().size();
    for (unsigned int i = 0; i<l2; i++){
        int x = p2->getunitlist()[i]->getposX();
        int y = p2->getunitlist()[i]->getposY();
        if (x == posx && y == posy){
            b = true;
            break;
        }
    }
    return b;
}

void Game::moveunit(int x, int y, int i){
    dijkstra dijk = dijkstra (this,i);
    int c = dijk.cost(x,y);
    if (c <= actif->getunitlist()[i]->getmp()){
        actif->getunitlist()[i]->move(x, y, c);
    }
    actif->getunitlist()[i]->setselected(false);
}


void Game::endgame(){
    if (iaplay){
        int n = 0;
        unsigned int l = allbat.size();
        for (unsigned int i = 0; i<l; i++){
            if (allbat[i]->getcamp() == 2){
                n++;
            }
        }
        if (n == l){
            finish = true;
            cout<<"tour fin "<<tour<<endl;
            EndMenu* menu = new EndMenu(mw,0,tour);
            menu->exec();
        }
    } else {
        int n1 = 0;
        int n2 = 0;
        unsigned int l = allbat.size();
        for (unsigned int i = 0; i<l; i++){
            if (allbat[i]->getcamp() == 1){
                n1++;
            } else if (allbat[i]->getcamp() == 2){
                n2++;
            }
        }
        if (n1 == 0){
            finish = true;
            EndMenu* menu = new EndMenu(mw,2,tour);
            menu->exec();
        } else if (n2 == 0){
            finish = true;
            EndMenu* menu = new EndMenu(mw,1,tour);
            menu->exec();
        }
    }
}

void Game::attaque(int mx,int my,int j){
    int xo = actif->getunitlist()[j]->getposX();
    int yo = actif->getunitlist()[j]->getposY();
    int dx = mx-xo;
    int dy = my-yo;
    if (abs(dx)+abs(dy) <=1 && actif->getunitlist()[j]->getatt()){
        unsigned int l = inactif->getunitlist().size();
        for (unsigned int i = 0; i<l; i++){
            int x = inactif->getunitlist()[i]->getposX();
            int y = inactif->getunitlist()[i]->getposY();
            if (x == mx && y == my){
                int d = damage(actif->getunitlist()[j],inactif->getunitlist()[i],x,y);
                bool b = inactif->getunitlist()[i]->attacked(d);
                actif->getunitlist()[j]->setselected(false);
                if (b){
                    int d2 = damage(inactif->getunitlist()[i],actif->getunitlist()[j],xo,yo);
                    bool a = actif->getunitlist()[j]->attacked(d2);
                    if(a == false){
                        actif->deleteunit(j);
                    }
                } else {
                    inactif->deleteunit(i);
                }
                break;
            }
        }
        unsigned int l2 = actif->getunitlist().size();
        for (unsigned int i = 0; i<l2; i++){
            int x = actif->getunitlist()[i]->getposX();
            int y = actif->getunitlist()[i]->getposY();
            if (x == mx && y == my){
                actif->getunitlist()[j]->setselected(false);
                actif->fusion(j,i);
                break;
            }
        }
    }
}

void Game::capture(){
    unsigned int l = actif->getunitlist().size();
    for (unsigned int i = 0; i<l; i++){
        if (actif->getunitlist()[i]->getatt()){
            int xu = actif->getunitlist()[i]->getposX();
            int yu = actif->getunitlist()[i]->getposY();
            unsigned int l2 = allbat.size();
            for (unsigned int j=0; j<l2; j++){
                if((allbat[j]->getcamp() != 1 && actif == p1)||(allbat[j]->getcamp() != 2 && actif == p2)){
                    int xb = allbat[j]->getposX();
                    int yb = allbat[j]->getposY();                   
                    if (xu == xb && yu == yb){
                        int a = actif->getunitlist()[i]->getpv();
                        allbat[j]->captured(a);
                        actif->getunitlist()[i]->setatt(false);
                        if (allbat[j]->getcapture()<=0){
                            int t = allbat[j]->getnum();
                            if (actif == p1){
                                allbat[j]->setcamp(1);
                                if (t == 35 or t == 123){
                                    allbat[j]->setnum(92);
                                } else if (t == 34 or t == 125){
                                    allbat[j]->setnum(95);
                                } else if (t == 36 or t == 124){
                                    allbat[j]->setnum(93);
                                }
                            } else if (actif == p2){
                                allbat[j]->setcamp(2);
                                if (t == 35 or t == 92){
                                    allbat[j]->setnum(123);
                                } else if (t == 34 or t == 95){
                                    allbat[j]->setnum(125);
                                } else if (t == 36 or t == 93){
                                    allbat[j]->setnum(124);
                                }
                            }
                            allbat[j]->setcapture(20);
                        }
                    }
                }
            }
        }
    }
    endgame();
}


int Game::damage(Unit* ua, Unit* ud,int x,int y){
    int ta = ua->gettype();
    int td = ud->gettype();

    int B[11][11];  // B[atk][def]

    B[0][0] = 55;
    B[0][1] = 45;
    B[0][2] = 12;
    B[0][3] = 5;
    B[0][4] = 5;
    B[0][5] = 1;
    B[0][6] = 1;
    B[0][7] = 1;
    B[0][8] = 7;
    B[0][9] = 0;
    B[0][10] = 0;

    B[1][0] = 65;
    B[1][1] = 55;
    B[1][2] = 85;
    B[1][3] = 65;
    B[1][4] = 55;
    B[1][5] = 15;
    B[1][6] = 5;
    B[1][7] = 15;
    B[1][8] = 9;
    B[1][9] = 0;
    B[1][10] = 0;

    B[2][0] = 70;
    B[2][1] = 65;
    B[2][2] = 35;
    B[2][3] = 4;
    B[2][4] = 6;
    B[2][5] = 1;
    B[2][6] = 1;
    B[2][7] = 1;
    B[2][8] = 12;
    B[2][9] = 0;
    B[2][10] = 0;

    B[3][0] = 105;
    B[3][1] = 105;
    B[3][2] = 60;
    B[3][3] = 45;
    B[3][4] = 25;
    B[3][5] = 10;
    B[3][6] = 1;
    B[3][7] = 5;
    B[3][8] = 120;
    B[3][9] = 65;
    B[3][10] = 75;

    B[4][0] = 75;
    B[4][1] = 70;
    B[4][2] = 85;
    B[4][3] = 65;
    B[4][4] = 55;
    B[4][5] = 15;
    B[4][6] = 10;
    B[4][7] = 15;
    B[4][8] = 10;
    B[4][9] = 0;
    B[4][10] = 0;

    B[5][0] = 105;
    B[5][1] = 95;
    B[5][2] = 105;
    B[5][3] = 105;
    B[5][4] = 85;
    B[5][5] = 55;
    B[5][6] = 25;
    B[5][7] = 45;
    B[5][8] = 12;
    B[5][9] = 0;
    B[5][10] = 0;

    B[6][0] = 135;
    B[6][1] = 125;
    B[6][2] = 195;
    B[6][3] = 195;
    B[6][4] = 180;
    B[6][5] = 125;
    B[6][6] = 65;
    B[6][7] = 115;
    B[6][8] = 22;
    B[6][9] = 0;
    B[6][10] = 0;

    B[7][0] = 125;
    B[7][1] = 115;
    B[7][2] = 125;
    B[7][3] = 115;
    B[7][4] = 105;
    B[7][5] = 75;
    B[7][6] = 35;
    B[7][7] = 55;
    B[7][8] = 22;
    B[7][9] = 0;
    B[7][10] = 0;

    B[8][0] = 75;
    B[8][1] = 75;
    B[8][2] = 55;
    B[8][3] = 25;
    B[8][4] = 55;
    B[8][5] = 25;
    B[8][6] = 10;
    B[8][7] = 20;
    B[8][8] = 65;
    B[8][9] = 0;
    B[8][10] = 0;

    B[9][0] = 0;
    B[9][1] = 0;
    B[9][2] = 0;
    B[9][3] = 0;
    B[9][4] = 0;
    B[9][5] = 0;
    B[9][6] = 0;
    B[9][7] = 0;
    B[9][8] = 100;
    B[9][9] = 55;
    B[9][10] = 100;

    B[10][0] = 110;
    B[10][1] = 110;
    B[10][2] = 105;
    B[10][3] = 95;
    B[10][4] = 105;
    B[10][5] = 95;
    B[10][6] = 35;
    B[10][7] = 90;
    B[10][8] = 0;
    B[10][9] = 0;
    B[10][10] = 0;


    int b = B[ta][td];
    int def = ter[y*SIZEMAP_X + x]->getdef();

    int d = b*ua->getpv()*(100-def*ud->getpv())/10000;
    return d;

}

std::tuple<int,int> Game::pressed(int mx, int my){
    bool oneselected = false;
    unsigned int l = actif->getunitlist().size();
    int r1=100;
    int r2=100;
    nombreType=100;
    for (int i = 0; i<l; i++){
        if (actif->getunitlist()[i]->getselected()){
            oneselected = true;
            if (isobstacle(mx,my) == false){
                r1=i;
                r2=0;
                moveunit(mx, my, i);
            } else {
                if (actif->getunitlist()[i]->getposX() == mx && actif->getunitlist()[i]->getposY() == my){
                    actif->getunitlist()[i]->setselected(false);
                } else {
                    r1=i;
                    r2=1;
                    attaque(mx,my,i);
                }
            }
        }
    }
    bool isunit = false;
    if (oneselected == false){
        for (unsigned int i = 0; i<l; i++){
            int x = actif->getunitlist()[i]->getposX();
            int y = actif->getunitlist()[i]->getposY();
            if (x == mx && y == my){
                actif->getunitlist()[i]->setselected(true);
                isunit = true;
                break;
            }
        }
    }
    if (oneselected == false && isunit == false){
        unsigned int a = allbat.size();
        for(unsigned int i = 0; i<a; i++){
            if ((allbat[i]->getcamp() == 1 && actif == p1) || (allbat[i]->getcamp() == 2 && actif == p2)){
                int x = allbat[i]->getposX();
                int y = allbat[i]->getposY();
                if (x==mx && y==my){
                    if (isobstacle(mx,my)==false){
                        Menu* menu = new Menu(mw,this,x,y);
                        r2=4;
                        menu->exec();
                        r1=nombreType;
                        actif->buyUnit(r1,mx,my);
                    }

                }
            }
        }
    }
    return std::make_tuple(r1,r2);

}

vector <Terrain*> Game::getter(){
    return this->ter;
}
vector <Batiment*> Game::getallbat(){
    return this->allbat;
}
Player* Game::getp1(){
    return this->p1;
}
Player* Game::getp2(){
    return this->p2;
}
Player* Game::getactif(){
    return this->actif;
}
Player* Game::getinactif(){
    return this->inactif;
}
int Game::gettour(){
    return this->tour;
}
bool Game::getfinish(){
    return this->finish;
}
int Game::getnombreType(){
    return this->nombreType;
}
void Game::setnombreType(int i){
    this->nombreType=i;
}
