#include "menu.h"
#include <QPushButton>

Menu::Menu(QWidget*parent, Game* game, int x, int y) : QDialog()
{
    this->game = game;
    this->x = x;
    this->y = y;

    setFixedSize(630,380);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("QDialog { background : darkGreen }");

    QPushButton*bouton_infantry = new QPushButton("Infantry 1000",this);
    bouton_infantry->setGeometry(20,20,280,40);
    bouton_infantry->setFont(QFont("Comic Sans MS",20));
    bouton_infantry->setStyleSheet("background-color: darkCyan;");
    bouton_infantry->show();


    QObject::connect(bouton_infantry,SIGNAL(clicked()),this,SLOT(infantry()));

    QPushButton*bouton_mech = new QPushButton("Mech 3000",this);
    bouton_mech->setGeometry(20,80,280,40);
    bouton_mech->setFont(QFont("Comic Sans MS",20));
    bouton_mech->setStyleSheet("background-color: darkCyan;");
    bouton_mech->show();

    QObject::connect(bouton_mech,SIGNAL(clicked()),this,SLOT(mech()));

    QPushButton*bouton_recon = new QPushButton("Recon 4000",this);
    bouton_recon->setGeometry(20,140,280,40);
    bouton_recon->setFont(QFont("Comic Sans MS",20));
    bouton_recon->setStyleSheet("background-color: darkCyan;");
    bouton_recon->show();

    QObject::connect(bouton_recon,SIGNAL(clicked()),this,SLOT(recon()));

    QPushButton*bouton_antiair = new QPushButton("Anti-air 8000",this);
    bouton_antiair->setGeometry(20,200,280,40);
    bouton_antiair->setFont(QFont("Comic Sans MS",20));
    bouton_antiair->setStyleSheet("background-color: darkCyan;");
    bouton_antiair->show();

    QObject::connect(bouton_antiair,SIGNAL(clicked()),this,SLOT(antiair()));

    QPushButton*bouton_tank = new QPushButton("Tank 7000",this);
    bouton_tank->setGeometry(20,260,280,40);
    bouton_tank->setFont(QFont("Comic Sans MS",20));
    bouton_tank->setStyleSheet("background-color: darkCyan;");
    bouton_tank->show();

    QObject::connect(bouton_tank,SIGNAL(clicked()),this,SLOT(tank()));

    QPushButton*bouton_mdtank = new QPushButton("Md Tank 16000",this);
    bouton_mdtank->setGeometry(20,320,280,40);
    bouton_mdtank->setFont(QFont("Comic Sans MS",20));
    bouton_mdtank->setStyleSheet("background-color: darkCyan;");
    bouton_mdtank->show();

    QObject::connect(bouton_mdtank,SIGNAL(clicked()),this,SLOT(mdtank()));

    QPushButton*bouton_megatank = new QPushButton("Mega Tank 28000",this);
    bouton_megatank->setGeometry(330,20,280,40);
    bouton_megatank->setFont(QFont("Comic Sans MS",20));
    bouton_megatank->setStyleSheet("background-color: darkCyan;");
    bouton_megatank->show();

    QObject::connect(bouton_megatank,SIGNAL(clicked()),this,SLOT(megatank()));

    QPushButton*bouton_neotank = new QPushButton("Neotank 22000",this);
    bouton_neotank->setGeometry(330,80,280,40);
    bouton_neotank->setFont(QFont("Comic Sans MS",20));
    bouton_neotank->setStyleSheet("background-color: darkCyan;");
    bouton_neotank->show();

    QObject::connect(bouton_neotank,SIGNAL(clicked()),this,SLOT(neotank()));

    QPushButton*bouton_bcopter = new QPushButton("B-Copter 9000",this);
    bouton_bcopter->setGeometry(330,140,280,40);
    bouton_bcopter->setFont(QFont("Comic Sans MS",20));
    bouton_bcopter->setStyleSheet("background-color: darkCyan;");
    bouton_bcopter->show();

    QObject::connect(bouton_bcopter,SIGNAL(clicked()),this,SLOT(bcopter()));

    QPushButton*bouton_fighter = new QPushButton("Fighter 20000",this);
    bouton_fighter->setGeometry(330,200,280,40);
    bouton_fighter->setFont(QFont("Comic Sans MS",20));
    bouton_fighter->setStyleSheet("background-color: darkCyan;");
    bouton_fighter->show();

    QObject::connect(bouton_fighter,SIGNAL(clicked()),this,SLOT(fighter()));

    QPushButton*bouton_bomber = new QPushButton("Bomber 22000",this);
    bouton_bomber->setGeometry(330,260,280,40);
    bouton_bomber->setFont(QFont("Comic Sans MS",20));
    bouton_bomber->setStyleSheet("background-color: darkCyan;");
    bouton_bomber->show();

    QObject::connect(bouton_bomber,SIGNAL(clicked()),this,SLOT(bomber()));

    QPushButton*bouton_return = new QPushButton("Back",this);
    bouton_return->setGeometry(330,320,280,40);
    bouton_return->setFont(QFont("Comic Sans MS",20));
    bouton_return->setStyleSheet("background-color: darkRed;");
    bouton_return->show();

    QObject::connect(bouton_return,SIGNAL(clicked()),this, SLOT(close()));

}

void Menu::infantry(){
    game->setnombreType(0);
    this->close();

}


void Menu::mech(){
game->setnombreType(1);
this->close();
}

void Menu::recon(){
    game->setnombreType(2);
    this->close();
}

void Menu::antiair(){
    game->setnombreType(3);
    this->close();
}

void Menu::tank(){
    game->setnombreType(4);
    this->close();
}

void Menu::mdtank(){
    game->setnombreType(5);
    this->close();
}

void Menu::megatank(){
    game->setnombreType(6);
    this->close();
}

void Menu::neotank(){
    game->setnombreType(7);
    this->close();
}

void Menu::bcopter(){
    game->setnombreType(8);
    this->close();
}

void Menu::fighter(){
    game->setnombreType(9);
    this->close();
}

void Menu::bomber(){
    game->setnombreType(10);
    this->close();
}

