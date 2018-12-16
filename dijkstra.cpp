#include "dijkstra.h"
#include "head.h"


std::vector<nodes *> dijkstra::getlistNodes()
{
    return this->listNodes;
}

dijkstra::dijkstra(Game* g, int unit) // ajouter bool all pour savoir si on s'arrete ou pas
{
        Unit* u=g->getactif()->getunitlist()[unit];

        vector <Terrain*> ter = g->getter();
        this->listNodes.push_back(new nodes(u->getposX(),u->getposY(),0,true,false));
        int type = u->getmovetype();
        int mpMoveMax= u->getmp();

        int mp=0;
        int gh=10;

        while (mp<=mpMoveMax && gh >0){
            // renvoyer cout des deplacement et faire une fonction pour les 4 cote
            //attention il faut aussi que tous les points ne soient plus en waiting ou at use
            int minmp=100;
            unsigned int bestNode=0;
            for (unsigned int j=0; j<this->listNodes.size();j++){
                if (this->listNodes[j]->getmp()<minmp && this->listNodes[j]->getsaved()==false){
                    minmp=this->listNodes[j]->getmp();
                    bestNode = j;
                    mp=minmp;
                }
            }

            this->listNodes[bestNode]->setsaved(true);
            this->listNodes[bestNode]->setwaiting(false);

            int x = this->listNodes[bestNode]->getposX();
            int y = this->listNodes[bestNode]->getposY();
            bool test=false;



            //gauche
            int xg=x-1;
            for (unsigned int i=0; i<this->listNodes.size();i++){

                if (xg == this->listNodes[i]->getposX() && y == this->listNodes[i]->getposY()){
                    test = true;

                    if (this->listNodes[i]->getwaiting() && this->listNodes[i]->getsaved()==false) {
                       if (this->listNodes[i]->getmp() > this->listNodes[bestNode]->getmp() + this->listNodes[i]->getCasemp(xg,y,type,ter)
                               && (this->listNodes[bestNode]->getmp() + this->listNodes[i]->getCasemp(xg,y,type,ter) <= mpMoveMax)){
                            this->listNodes[i]->setmp(this->listNodes[bestNode]->getmp() + this->listNodes[i]->getCasemp(xg,y,type,ter));
                        }
                    }
                }
           }

            if (test==false){
                int add = getMp(xg,y,type,ter);
                if (this->listNodes[bestNode]->getmp() + add <= mpMoveMax){
                    this->listNodes.push_back(new nodes(xg,y,this->listNodes[bestNode]->getmp() + add,true));
                }
            }


            //droite
            test=false;
            int xd = x+1;
            for (unsigned int i=0; i<this->listNodes.size();i++){
                if (xd == this->listNodes[i]->getposX() && y ==this->listNodes[i]->getposY()){
                    test = true;
                    if (this->listNodes[i]->getwaiting() && this->listNodes[i]->getsaved()==false){
                       if (this->listNodes[i]->getmp() > this->listNodes[bestNode]->getmp() + this->listNodes[i]->getCasemp(xd,y,type,ter)
                               && (this->listNodes[bestNode]->getmp() + this->listNodes[i]->getCasemp(xd,y,type,ter) <= mpMoveMax)){
                            this->listNodes[i]->setmp(this->listNodes[bestNode]->getmp() + this->listNodes[i]->getCasemp(xd,y,type,ter));

                       }
                    }
                }
            }

            if (test==false){
                int add = getMp(xd,y,type,ter);
                if (this->listNodes[bestNode]->getmp() + add <= mpMoveMax){
                    this->listNodes.push_back(new nodes(xd,y,this->listNodes[bestNode]->getmp() + add,true));
                }
            }



           //haut
           test=false;
           int yh = y-1;
           for (unsigned int i=0; i<this->listNodes.size();i++){
               if (yh == this->listNodes[i]->getposY() && x ==this->listNodes[i]->getposX()){
                   test = true;

                   if (this->listNodes[i]->getwaiting() && this->listNodes[i]->getsaved()==false){
                      if (this->listNodes[i]->getmp()>this->listNodes[bestNode]->getmp() + this->listNodes[i]->getCasemp(x,yh,type,ter)
                              && (this->listNodes[bestNode]->getmp() + this->listNodes[i]->getCasemp(x,yh,type,ter) <= mpMoveMax)){
                           this->listNodes[i]->setmp(this->listNodes[bestNode]->getmp() + this->listNodes[i]->getCasemp(x,yh,type,ter));

                      }
                   }
                }
          }

           if (test==false){
               int add = getMp(x,yh,type,ter);
               if (this->listNodes[bestNode]->getmp() + add <= mpMoveMax){
                   this->listNodes.push_back(new nodes(x,yh,this->listNodes[bestNode]->getmp() + add,true));
               }
           }


           //bas
           test=false;
           int yb = y+1;
           for (unsigned int i=0; i<this->listNodes.size();i++){
               if (yb == listNodes[i]->getposY() && x ==this->listNodes[i]->getposX()){
                   test = true;

                   if(this->listNodes[i]->getwaiting() && this->listNodes[i]->getsaved()==false){
                      if (this->listNodes[i]->getmp()>this->listNodes[bestNode]->getmp() + this->listNodes[i]->getCasemp(x,yb,type,ter)
                              && (this->listNodes[bestNode]->getmp() + this->listNodes[i]->getCasemp(x,yb,type,ter) <= mpMoveMax)){
                           this->listNodes[i]->setmp(this->listNodes[bestNode]->getmp() + this->listNodes[i]->getCasemp(x,yb,type,ter));

                      }

                   }
                }


          }

          if (test==false){
               int add = getMp(x,yb,type,ter);
               if (this->listNodes[bestNode]->getmp() + add <= mpMoveMax){
                   this->listNodes.push_back(new nodes(x,yb,this->listNodes[bestNode]->getmp() + add,true));
               }
           }

          //suprimer les nodes avec mp>mpmax; et verifier qu'il n'y ait pas d'obsbtacle (unité adverse

           mp = this->listNodes[bestNode]->getmp();
           gh=0;
           for (unsigned int i=0; i<this->listNodes.size();i++){
               if(this->listNodes[i]->getwaiting()){
                   gh++;
               }
           }
     }
        listNodes.erase(listNodes.begin());
}


int dijkstra::getMp(int x, int y, int type, std::vector<Terrain *> ter)
{
    for (unsigned int i=0; i<ter.size(); i++){
        if (ter[i]->getposX()==x && ter[i]->getposY()==y){
            int n = ter[i]->getmt(type);
            return n;
        }
    }
}

int dijkstra::cost(int x, int y)
{
    int cost=1000;
    for (int i=0; i<this->listNodes.size();i++){
        if (x == this->listNodes[i]->getposX() && y == this->listNodes[i]->getposY()) {
            cost = this->listNodes[i]->getmp();
            break;
        }
    }
    return cost;
}



