#include "ui_gameinterface.h"
#include "enviroment.h"
#include "gameinterface.h"
#include "switcher.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QInputDialog>
#include <QLabel>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <QTime>






void GameInterface::paintEvent(QPaintEvent *event){
    static int times = 0;
    //qDebug()<<"Draw again."<<times++<<gameFormat;
    drawer->draw();
}


//------------------------gameEvent-----------------------


int GameInterface::mapPos(int x,int y,int &a,int &b){
   a=(y-startX)/game.getLen()+1;
   b=(x-startY)/game.getLen()+1;
}


void GameInterface::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && !game.nowWay){
        int a,b;
        mapPos(event->x(),event->y(),a,b);
        qDebug()<<"mouse press: "<<a<<" "<<b;
        if (game.blocks[a][b].status == source){
            isTracking = 1;
            game.nowWay = game.map[a][b];
            for (int i=1;i<=game.waysTot;i++) if (game.ways[i].getColor() == game.blocks[a][b].color){
                game.ways[i].clearTail();
            }
        }
        this->update();
    }
}


void GameInterface::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() == Qt::LeftButton && isTracking){
        //qDebug()<<"!";
        int a,b;
        mapPos(event->x(),event->y(),a,b);
        //qDebug()<<"mouse move: "<<a<<" "<<b<<" nowWay:"<<ways[nowWay].head().loc;
        if (game.blocks[a][b].isNeighbour(game.ways[game.nowWay].last())){
            if ( game.blocks[a][b].status == gothrough && game.blocks[a][b].color != game.ways[game.nowWay].getColor()){
                qDebug()<<"gothrough && color differrnt: "<<game.blocks[a][b].color<<" "<<game.ways[game.nowWay].getColor();
                game.cutWay(game.map[a][b]);
                this->update();
                qDebug()<<"cut way complete.";
            }
            //未标记点或终点
            if (game.blocks[a][b].status == unmark || (game.blocks[a][b].status == source && game.blocks[a][b].color == game.ways[game.nowWay].getColor() && !game.blocks[a][b].isSame(game.ways[game.nowWay].head()))){
                game.ways[game.nowWay].add(&game.blocks[a][b]);
                if (game.blocks[a][b].status == unmark){
                    game.blocks[a][b].status = gothrough;
                    game.blocks[a][b].color  = game.ways[game.nowWay].getColor();
                    game.map[a][b]=game.nowWay;
                }
          //      qDebug()<<"mark && size:"<<ways[nowWay].size();
                if (game.blocks[a][b].status == source){
                    game.nowWay=0;
                    isTracking=0;
                }
            }
        }
        this->update();
    }
}


void GameInterface::mouseReleaseEvent(QMouseEvent *event){

    if (event->button() == Qt::LeftButton){
        if (isTracking){
            int a,b;
            mapPos(event->x(),event->y(),a,b);
            //到达终点合法,否则撤销已画路径
            if (game.blocks[a][b].status == source){
            }else{
                game.clearWay(game.nowWay);
                this->update();
            }
            isTracking = 0;
            game.nowWay = 0;
        }
        if (checkGameComplete()){
            gameComplete();
        }
        if (checkGameFinishHalf()){
            gameFinishHalf();
        }
        this->update();
    }
}



//-------------------------gameControl--------------------------

void GameInterface::startGame(){
    qDebug()<<"game srart";

    game.makeSource();
    this->update();
}

void GameInterface::restartGame(){
    qDebug()<<"game restarting...";
    isTracking = 0;
    game.nowWay=0;
    for (int i=1;i<=game.waysTot;i++) game.ways[i].initWay();
    game.waysTot=0;
    game.makeBlocksInfo();
    startGame();
}

void GameInterface::quitGame(){
    exit(0);
}



//点击[选择游戏大小]
/*void GameInterface::on_action_triggered()
{
    chooseForm *choose = new chooseForm(0);
    choose->exec();
    this->update();
    restartGame();
}*/

bool GameInterface::checkGameComplete(){
    for (int i=1;i<=game.gameFormat;i++)
        for (int j=1;j<=game.gameFormat;j++){
            if (game.blocks[i][j].status == unmark){
                return false;
            }
        }
    return true;
}

void GameInterface::gameComplete(){
    int ret = QMessageBox::question(0,"恭喜你","是否再来一局?",QMessageBox::Yes,QMessageBox::No);
    if (ret == QMessageBox::Yes){
        restartGame();
    }else{
        quitGame();
    }
}

bool GameInterface::checkGameFinishHalf(){
    int count=0;
    for (int i=1;i<=game.waysTot;i++) if (game.ways[i].size()>1){
        count++;
    }
    qDebug()<<"game finish: "<<count<<" needed: "<<game.waysTot/2;
    return count>=game.waysTot/2;
}

void GameInterface::gameFinishHalf(){
    int ret = QMessageBox::question(0,"已经完成一半了","继续?",QMessageBox::Yes,QMessageBox::No);
    if (ret == QMessageBox::Yes){

    }else{
        //quitGame();
        restartGame();
    }
}

GameInterface::GameInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameInterface)
{
    qDebug()<<"gameInterface maked";
    ui->setupUi(this);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    drawer = new Drawer(this,&game);
    this->update();
//    qDebug()<<"rect2: "<<game.blocks[3][3].rect;

    startGame();
}

GameInterface::~GameInterface()
{
    delete ui;
}





void GameInterface::on_back_button_clicked()
{
    switcher.showInterface("choose");
}
