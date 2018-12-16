#include "menuend.h"
#include<QPushButton>

MenuEnd::MenuEnd(QWidget *parent,int p) : QDialog()
{

    setFixedSize(630,380);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("QDialog { background : darkGreen }");

    QPushButton*bouton_return = new QPushButton("Back",this);
    bouton_return->setGeometry(330,320,280,40);
    bouton_return->setFont(QFont("Comic Sans MS",20));
    bouton_return->setStyleSheet("background-color: darkRed;");
    bouton_return->show();

    QObject::connect(bouton_return,SIGNAL(clicked()),this, SLOT(close()));

}
