#include "head.h"
#include "game.h"

#include <QApplication>
#include <QPainter>
#include <QKeyEvent>
#include <QPushButton>
#include <vector>
#include <iostream>
using namespace std;

int const sizecase = min(SIZE_WINDOWS_X/SIZEMAP_X,SIZE_WINDOWS_Y/SIZEMAP_Y);

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadimage();
    reseau=false; //true pour activer le réseau

    if (reseau){
    server = new QTcpServer();
    if(! server->listen(QHostAddress::Any, 8123)) {
       std::cout << "I am a client" << std::endl;
       other = new QTcpSocket();
       connect(other, SIGNAL(connected()), this, SLOT(onConnected()));
       other->connectToHost("127.0.0.1", 8123);
        connect(other, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
       } else {
           std::cout << "I am the server" << std::endl;
           other = nullptr;
       }

    connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    } else {
       myTurn=true;
    }


    this->g = new Game(this);

    QPushButton*bouton_turn = new QPushButton("FIN DE TOUR",this);
    bouton_turn->setGeometry(1000,80,280,40);
    bouton_turn->setFont(QFont("Comic Sans MS",20));
    bouton_turn->setStyleSheet("background-color: darkCyan;");
    bouton_turn->show();
    QObject::connect(bouton_turn,SIGNAL(clicked()),this,SLOT(turn()));

    QPushButton*bouton_capt = new QPushButton("CAPTURE",this);
    bouton_capt->setGeometry(1000,400,280,40);
    bouton_capt->setFont(QFont("Comic Sans MS",20));
    bouton_capt->setStyleSheet("background-color: darkGrey;");
    bouton_capt->show();
    QObject::connect(bouton_capt,SIGNAL(clicked()),this,SLOT(capt()));

    QPushButton*bouton_return = new QPushButton("EXIT",this);
    bouton_return->setGeometry(1000,600,200,40);
    bouton_return->setFont(QFont("Comic Sans MS",20));
    bouton_return->setStyleSheet("background-color: darkRed;");
    bouton_return->show();

    QObject::connect(bouton_return,SIGNAL(clicked()),this, SLOT(close()));

}

MainWindow::~MainWindow(){
    delete ui;
    delete g;
}

void MainWindow::loadimage(){

    image[1] = QPixmap(":/images/1_plain.gif");
    image[2] = QPixmap(":/images/2_mountain.gif");
    image[3] = QPixmap(":/images/3_wood.gif");
    image[4] = QPixmap(":/images/4_hriver.gif");
    image[5] = QPixmap(":/images/5_vriver.gif");
    image[7] = QPixmap(":/images/7_esriver.gif");
    image[8] = QPixmap(":/images/8_swriver.gif");
    image[9] = QPixmap(":/images/9_wnriver.gif");
    image[10] = QPixmap(":/images/10_neriver.gif");
    image[15] = QPixmap(":/images/15_hroad.gif");
    image[16] = QPixmap(":/images/16_vroad.gif");
    image[18] = QPixmap(":/images/18_esroad.gif");
    image[19] = QPixmap(":/images/19_swroad.gif");
    image[20] = QPixmap(":/images/20_wnroad.gif");
    image[21] = QPixmap(":/images/21_neroad.gif");
    image[22] = QPixmap(":/images/22_eswroad.gif");
    image[23] = QPixmap(":/images/23_swnroad.gif");
    image[24] = QPixmap(":/images/24_wneroad.gif");
    image[25] = QPixmap(":/images/25_nesroad.gif");
    image[26] = QPixmap(":/images/26_hbridge.gif");
    image[29] = QPixmap(":/images/29_hshoal.gif");
    image[30] = QPixmap(":/images/30_hshoaln.gif");
    image[33] = QPixmap(":/images/33_reef.gif");
    image[101] = QPixmap(":/images/101_vpipe.gif");
    image[102] = QPixmap(":/images/102_hpipe.gif");
    image[104] = QPixmap(":/images/104_espipe.gif");
    image[106] = QPixmap(":/images/106_wnpipe.gif");
    image[107] = QPixmap(":/images/107_npipeend.gif");
    image[108] = QPixmap(":/images/108_epipeend.gif");
    image[109] = QPixmap(":/images/109_spipeend.gif");
    image[110] = QPixmap(":/images/110_wpipeend.gif");

    image[34] = QPixmap(":/images/34_neutralcity.gif");
    image[35] = QPixmap(":/images/35_neutralbase.gif");
    image[36] = QPixmap(":/images/36_neutralairport.gif");

    image[92] = QPixmap(":/images/92_orangestarbase.gif");
    image[93] = QPixmap(":/images/93_orangestarairport.gif");
    image[95] = QPixmap(":/images/95_orangestarcity.gif");

    image[123] = QPixmap(":/images/123_bluemoonbase.gif");
    image[124] = QPixmap(":/images/124_bluemoonairport.gif");
    image[125] = QPixmap(":/images/125_bluemooncity.gif");


    // unit orange
    imageorange[0] = QPixmap(":/images/osinfantry.gif");
    imageorange[1] = QPixmap(":/images/osmech.gif");
    imageorange[2] = QPixmap(":/images/osrecon.gif");
    imageorange[3] = QPixmap(":/images/osanti-air.gif");
    imageorange[4] = QPixmap(":/images/ostank.gif");
    imageorange[5] = QPixmap(":/images/osmd.tank.gif");
    imageorange[6] = QPixmap(":/images/osmegatank.gif");
    imageorange[7] = QPixmap(":/images/osneotank.gif");
    imageorange[8] = QPixmap(":/images/osb-copter.gif");
    imageorange[9] = QPixmap(":/images/osfighter.gif");
    imageorange[10] = QPixmap(":/images/osbomber.gif");


    // unit blue
    imageblue[0] = QPixmap(":/images/bminfantry.gif");
    imageblue[1] = QPixmap(":/images/bmmech.gif");
    imageblue[2] = QPixmap(":/images/bmrecon.gif");
    imageblue[3] = QPixmap(":/images/bmanti-air.gif");
    imageblue[4] = QPixmap(":/images/bmtank.gif");
    imageblue[5] = QPixmap(":/images/bmmd.tank.gif");
    imageblue[6] = QPixmap(":/images/bmmegatank.gif");
    imageblue[7] = QPixmap(":/images/bmneotank.gif");
    imageblue[8] = QPixmap(":/images/bmb-copter.gif");
    imageblue[9] = QPixmap(":/images/bmfighter.gif");
    imageblue[10] = QPixmap(":/images/bmbomber.gif");
}

void MainWindow::paintEvent(QPaintEvent* event){
   QPainter painter(this);
   if(!g->getfinish()){
       for (unsigned int i=0;i<SIZEMAP;i++){
            int n = g->getter()[i]->getnum();
            int x = g->getter()[i]->getposX();
            int y = g->getter()[i]->getposY();
            if (n==2 or n==34 or n==125 or n==95){
               painter.drawPixmap(x*sizecase,y*sizecase-15,sizecase,sizecase+15,image[n]);
            } else if (n==35 or n==123 or n==92){
               painter.drawPixmap(x*sizecase,y*sizecase-25,sizecase,sizecase+25,image[n]);
            } else if (n==36 or n==124 or n==93){
                painter.drawPixmap(x*sizecase,y*sizecase-5,sizecase,sizecase+5,image[n]);
            } else {
                painter.drawPixmap(x*sizecase,y*sizecase,sizecase,sizecase,image[n]);
            }
       }

       unsigned int l1 = g->getp1()->getunitlist().size();
       for (unsigned int i = 0; i<l1; i++){
           int x = g->getp1()->getunitlist()[i]->getposX();
           int y = g->getp1()->getunitlist()[i]->getposY();
           int t = g->getp1()->getunitlist()[i]->gettype();
           if (g->getp1()->getunitlist()[i]->getselected()){
               painter.fillRect(x*sizecase,y*sizecase,sizecase,sizecase,QColor(255,0,0,150));
               dijkstra dijk = dijkstra(g,i);
               for (unsigned int i=0; i<dijk.getlistNodes().size();i++){
                   int xdi = dijk.getlistNodes()[i]->getposX();
                   int ydi = dijk.getlistNodes()[i]->getposY();
                   int cdi = dijk.getlistNodes()[i]->getmp();
                   painter.fillRect(xdi*sizecase,ydi*sizecase,sizecase,sizecase,QColor(255,0,0,100));
                   painter.setPen(Qt::black);
                   QString s = QString::fromStdString(to_string(cdi));
                   painter.drawText(xdi*sizecase + 5,ydi*sizecase + 15,s);
               }
           }
           painter.drawPixmap(x*sizecase,y*sizecase,sizecase,sizecase,imageorange[t]);
           int pv = g->getp1()->getunitlist()[i]->getpv();
           painter.setPen(Qt::black);
           QString s = QString::fromStdString("pv "+to_string(pv));
           painter.drawText(x*sizecase,y*sizecase,s);

       }
       unsigned int l2 = g->getp2()->getunitlist().size();
       for (unsigned int i = 0; i<l2; i++){
           int x = g->getp2()->getunitlist()[i]->getposX();
           int y = g->getp2()->getunitlist()[i]->getposY();
           int t = g->getp2()->getunitlist()[i]->gettype();
           if (g->getp2()->getunitlist()[i]->getselected()){
               painter.fillRect(x*sizecase,y*sizecase,sizecase,sizecase,QColor(0,50,255,150));
               dijkstra dijk = dijkstra(g,i);
               for (unsigned int i=0; i<dijk.getlistNodes().size();i++){
                   int xdi = dijk.getlistNodes()[i]->getposX();
                   int ydi = dijk.getlistNodes()[i]->getposY();
                   int cdi = dijk.getlistNodes()[i]->getmp();
                   painter.fillRect(xdi*sizecase,ydi*sizecase,sizecase,sizecase,QColor(0,50,255,70));
                   painter.setPen(Qt::black);
                   QString s = QString::fromStdString(to_string(cdi));
                   painter.drawText(xdi*sizecase + 5,ydi*sizecase + 15,s);
               }
           }
           painter.drawPixmap(x*sizecase,y*sizecase,sizecase,sizecase,imageblue[t]);
           int pv = g->getp2()->getunitlist()[i]->getpv();
           painter.setPen(Qt::black);
           QString s = QString::fromStdString("pv "+to_string(pv));
           painter.drawText(x*sizecase,y*sizecase,s);
       }
       painter.fillRect(point.getposX()*sizecase,point.getposY()*sizecase,sizecase,sizecase,QColor(255,255,255,127));


       painter.setPen(Qt::black);
       if(g->getactif() == g->getp1()){
           painter.fillRect(1000,30,130,30,QColor(255,0,0,200));
           painter.drawText(1010,50,"tour du joueur orange");
       } else {
           painter.fillRect(1000,30,120,30,QColor(0,50,255,150));
           painter.drawText(1010,50,"tour du joueur bleu");
       }
       QString t = QString::fromStdString("tour : "+to_string(g->gettour()));
       painter.drawText(1200,50,t);

       int m1 = g->getp1()->getmoney();
       int m2 = g->getp2()->getmoney();
       QString s1 = QString::fromStdString("argent orange : "+to_string(m1));
       QString s2 = QString::fromStdString("argent bleu : "+to_string(m2));
       painter.drawText(1000,200,s1);
       painter.drawText(1000,250,s2);

       if (reseau){
           painter.drawText(1000, 550, QString("myTurn: ") + (myTurn ? "true" : "false"));
       }
   }
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    int x = point.getposX();
    int y = point.getposY();
    switch (event->key()) {

    case Qt::Key_A:
        point.move(x-1,y);
        break;
    case Qt::Key_E:
        point.move(x+1,y);
        break;
    case Qt::Key_Z:
        point.move(x,y-1);
        break;
    case Qt::Key_S:
        point.move(x,y+1);
        break;
    case Qt::Key_Q:
        g->pressed(x,y);
        break;
    }
    repaint();
}


void MainWindow::mousePressEvent(QMouseEvent *event){
    if(myTurn){
    int mx = event->x()/sizecase;
    int my = event->y()/sizecase;

    int i; int n;
    tie(i, n) = g->pressed(mx,my);

    if (reseau){
    QJsonObject move;
    move["action"]=n;
    move["newX"] = mx;
    move["newY"] = my;
    move["unit"] = i;
    sendJson(move);
    }




    repaint();
}
}


void MainWindow::turn(){
    if(myTurn)
       {
    g->endturn();

    if (reseau){
        QJsonObject endturn;
        endturn["action"]=2;
        sendJson(endturn);
        myTurn = false;
    }

    repaint();
    }
}

void MainWindow::capt(){
    if(myTurn){
    g->capture();
    if (reseau){
    QJsonObject capture;
    capture["action"]=3;
    sendJson(capture);
    }
    repaint();
    }
}

void MainWindow::onNewConnection() {
    std::cout << "A new client is connecting !" << std::endl;
    other = server->nextPendingConnection();
    connect(other, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(other, SIGNAL(readyRead()), this, SLOT(onData()));

        QJsonObject info;
        update();

        isConfigured = true;
        myTurn = false;

        sendJson(info);
        update();
}
void MainWindow::onConnected() {
    std::cout << "I am connected" << std::endl;
    connect(other, SIGNAL(readyRead()), this, SLOT(onData()));

}

void MainWindow::onDisconnected() {
    std::cout << "The other guy just disconnected" << std::endl;
}

void MainWindow::onData() {
    std::cout << "Some data !" << std::endl;
    if(currentSize == 0) {
         if(other->bytesAvailable() < 4)
             return;
             QDataStream in(other);
             in >> currentSize;
         }
         if(other->bytesAvailable() < currentSize)
            return;
         QByteArray data = other->read(currentSize);
         std::cout << data.toStdString() << std::endl;
         currentSize = 0;

         QJsonDocument doc = QJsonDocument::fromJson(data);
         QJsonObject json = doc.object();
         if(! isConfigured) {

             update();
             isConfigured = true;
             myTurn = true;
         } else {
             int newX = json["newX"].toInt();
             int newY = json["newY"].toInt();
             int action = json["action"].toInt();
             int unit = json["unit"].toInt();
             if(action ==0){
                g->moveunit(newX,newY,unit);
                update();
             }
             if(action ==1){
                g->attaque(newX,newY,unit);
                update();
             }
             if(action ==2){
                g->endturn();
                myTurn=true;
                update();
             }
             if(action ==3){
                g->capture();
                update();
             }
             if (action==4){
                 g->getactif()->buyUnit(unit,newX,newY);
             }

              update();
         }

         if(other->bytesAvailable() > 0){
            onData();
         }
}


void MainWindow::sendJson(QJsonObject obj) {
    QByteArray data = QJsonDocument(obj).toJson();
    QDataStream out(other);
    out << (quint32) data.length();
    other->write(data);
     std::cout << "Sending " << data.toStdString() << std::endl;
}
