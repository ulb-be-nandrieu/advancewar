#include "endmenu.h"
#include <QPushButton>
#include <Qpainter>

EndMenu::EndMenu(QWidget* parent, int p, int t) : QDialog ()
{
    setGeometry(400,200,400,300);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("QDialog { background : darkGrey }");

    if(p == 0){
        QPushButton*bouton_win = new QPushButton("IA win",this);
        bouton_win->setStyleSheet("background-color: Yellow;");

        bouton_win->setGeometry(70,60,260,40);
        bouton_win->setFont(QFont("Comic Sans MS",15));
        bouton_win->show();
    } else if(p == 1){
        QPushButton*bouton_win = new QPushButton("Player Orange win",this);
        bouton_win->setStyleSheet("background-color: Red;");

        bouton_win->setGeometry(70,60,260,40);
        bouton_win->setFont(QFont("Comic Sans MS",15));
        bouton_win->show();
    } else {
        QPushButton*bouton_win = new QPushButton("Player Blue win",this);
        bouton_win->setStyleSheet("background-color: darkCyan;");

        bouton_win->setGeometry(70,60,260,40);
        bouton_win->setFont(QFont("Comic Sans MS",15));
        bouton_win->show();
    }

    QPainter painter(this);
    painter.setPen(Qt::black);
    QString s = QString::fromStdString(std::to_string(t)+" tour");
    painter.drawText(100,150,s);

    QPushButton*bouton_return = new QPushButton("EXIT",this);
    bouton_return->setGeometry(100,180,200,40);
    bouton_return->setFont(QFont("Comic Sans MS",20));
    bouton_return->setStyleSheet("background-color: darkRed;");
    bouton_return->show();

    QObject::connect(bouton_return,SIGNAL(clicked()),this, SLOT(close()));






}
