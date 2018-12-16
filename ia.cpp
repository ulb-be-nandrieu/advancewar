#include "head.h"

Ia::Ia(Game* g)
{
    this->game = g;
}

void Ia::greedy(int n){
    bool capt = false;
    for(unsigned int j = 0; j<game->getallbat().size(); j++){
        if(game->getallbat()[j]->getposX() == game->getactif()->getunitlist()[n]->getposX() && game->getallbat()[j]->getposY() == game->getactif()->getunitlist()[n]->getposY()){
            if(game->getallbat()[j]->getcamp() != 2){
                capt = true;
                game->capture();
                break;
            }
        }
    }
    bool iscity = false;
    if (capt == false){
        dijkstra* dijk = new dijkstra(game,n);
        bool found = false;
        for(unsigned int j = 0; j<game->getallbat().size(); j++){
            if(game->getallbat()[j]->getcamp() != 2 && !game->isobstacle(game->getallbat()[j]->getposX(),game->getallbat()[j]->getposX())){
                for(unsigned int i = 0; i<dijk->getlistNodes().size(); i++){
                    if (game->getallbat()[j]->getposX() == dijk->getlistNodes()[i]->getposX() && game->getallbat()[j]->getposY() == dijk->getlistNodes()[i]->getposY()){
                        iscity = true;
                        game->getp2()->getunitlist()[n]->move(dijk->getlistNodes()[i]->getposX(), dijk->getlistNodes()[i]->getposY(), dijk->getlistNodes()[i]->getmp());
                        game->capture();
                        found = true;
                        break;
                    }
                }
                //            if (found){
                //                break;
                //            }
            }

        }
        if (iscity == false){
            unsigned int im = dijk->getlistNodes().size();
            unsigned int jm = game->getallbat().size();
            unsigned int dist[im][jm];
            for(unsigned int j = 0; j<jm; j++){
                if(game->getallbat()[j]->getcamp() != 2 && !game->isobstacle(game->getallbat()[j]->getposX(),game->getallbat()[j]->getposX())){
                    for(unsigned int i = 0; i<im; i++){
                        int dx = game->getallbat()[j]->getposX() - dijk->getlistNodes()[i]->getposX();
                        int dy = game->getallbat()[j]->getposY() - dijk->getlistNodes()[i]->getposY();
                        dist[i][j] = abs(dx)+abs(dy);
                    }
                }
            }

            //recherche du min -> m1
            unsigned int m1 = 0;
            unsigned int m2 = 0;
            for(unsigned int j = 0; j<jm; j++){
                if(game->getallbat()[j]->getcamp() != 2){
                    for(unsigned int i = 0; i<im; i++){
                        if (dist[i][j] < dist[m1][m2]){
                            m1 = i;
                            m2 = j;
                        }
                    }
                }
            }
            // fin

            if (!game->isobstacle(dijk->getlistNodes()[m1]->getposX(), dijk->getlistNodes()[m1]->getposY())){
               game->getp2()->getunitlist()[n]->move(dijk->getlistNodes()[m1]->getposX(), dijk->getlistNodes()[m1]->getposY(), dijk->getlistNodes()[m1]->getmp());
            }
        }
        delete dijk;
    }   
}

