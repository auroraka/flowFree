#include "ui_gameinterface.h"
#include "ui_gamedialog.h"
#include "enviroment.h"
#include "gameinterface.h"
#include "chooseinterface.h"
#include "textinfo.h"
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


QDialog *mydialog;


void GameInterface::paintEvent(QPaintEvent *event){
    //QPainter painter(this);
    //painter.drawEllipse(30,30,30,30);
    //return;
    //if (drawer!=NULL) delete drawer;

    drawer->painter = new QPainter(this);
    drawer->draw();
}


//------------------------gameEvent-----------------------


void GameInterface::getTextInfo(TextInfo text,int _level,int _id){
    text.print();
    if (text.transToGameInfo(game)){
        level=_level;
        id=_id;
        startGame();
    }else{
        qDebug()<<"[ERROR] game level document error!";
        QMessageBox::critical(this,"游戏错误","游戏关卡存档错误",QMessageBox::YesAll);
        exit(0);
    }
}

void GameInterface::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && !game.nowWay){
        int a,b;
        if (!game.getLoc(a,b,event->pos())) return;
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
        if (!game.getLoc(a,b,event->pos())) return;
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
            if (!game.getLoc(a,b,event->pos())) return;
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
            this->update();
            return;
        }
        if (checkGameFinishHalf()){
            gameFinishHalf();
            this->update();
            return;
        }
    }
}



//-------------------------gameControl--------------------------

void GameInterface::startGame(){
    qDebug()<<"game srart";

   // game.makeSource();
    this->update();
}

void GameInterface::restartGame(){
    if (mydialog != NULL){
        mydialog->reject();
        mydialog=NULL;
    }
    qDebug()<<"game restarting...";
    isTracking = 0;
    game.restart();
    startGame();
}

void GameInterface::quitGame(){
    exit(0);
}



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
    mydialog = new QDialog(this);
    Ui::GameDialog ui;
    ui.setupUi(mydialog);
    ui.pushButton->setText("next level");
    ui.pushButton_2->setText("play again");
    ui.label->setText("Well Done!");
    mydialog->show();
    connect(ui.pushButton,SIGNAL(clicked(bool)),this,SLOT(nextLevel()));
    connect(ui.pushButton_2,SIGNAL(clicked(bool)),this,SLOT(restartGame()));
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
    mydialog = new QDialog(this);
    Ui::GameDialog ui;
    ui.setupUi(mydialog);
    ui.pushButton->setText("keep play");
    ui.pushButton_2->setText("skip level");
    ui.label->setText("Almost there...");
    mydialog->show();
    connect(ui.pushButton,SIGNAL(clicked(bool)),this,SLOT(keepGame()));
    connect(ui.pushButton_2,SIGNAL(clicked(bool)),this,SLOT(nextLevel()));

}
void GameInterface::keepGame(){
    if (mydialog != NULL){
        mydialog->reject();
        mydialog=NULL;
    }
}

GameInterface::GameInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameInterface)
{
    qDebug()<<"gameInterface maked";
    ui->setupUi(this);
    this->hide();

    drawer = new Drawer(this,&game);

    //startGame();
}

GameInterface::~GameInterface()
{
    delete ui;
}

void GameInterface::connectTextInfo(ChooseInterface *choose){
    connect(choose,SIGNAL(sendTextInfo(TextInfo,int,int)),this,SLOT(getTextInfo(TextInfo,int,int)));
}



void GameInterface::on_back_button_clicked()
{
    isTracking = 0;
    game.reInit();
    switcher.showInterface("choose");
}

void GameInterface::on_previous_level_button_clicked()
{
    previousLevel();
}
void GameInterface::nextLevel(){
    if (mydialog != NULL){
        mydialog->reject();
        mydialog=NULL;
    }
    TextInfo text;
    int nid=id+1;
    if (text.loadGame(level,nid)){
        text.print();
        if (text.transToGameInfo(game)){
            id=nid;
            startGame();
        }else{
            qDebug()<<"[ERROR] game level document error!";
            QMessageBox::critical(this,"游戏错误","游戏关卡存档错误",QMessageBox::YesAll);
            exit(0);
        }
    }
}
void GameInterface::previousLevel(){
    if (mydialog != NULL){
        mydialog->reject();
        mydialog=NULL;
    }
    TextInfo text;
    int nid=id-1;
    if (nid<=0) return;
    if (text.loadGame(level,nid)){
        text.print();
        if (text.transToGameInfo(game)){
            id=nid;
            startGame();
        }else{
            qDebug()<<"[ERROR] game level document error!";
            QMessageBox::critical(this,"游戏错误","游戏关卡存档错误",QMessageBox::YesAll);
            exit(0);
        }
    }
}

void GameInterface::on_next_level_button_clicked()
{
    nextLevel();
}

void GameInterface::on_restart_button_clicked()
{
    restartGame();
}
