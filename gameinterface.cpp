#include "ui_gameinterface.h"
#include "enviroment.h"
#include "gameinterface.h"
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
void GameInterface::clearWay(int num){
    for (int i=1;i<game.ways[num].link.size();i++){
        game.map[game.ways[num].link[i]->loc.x()][game.ways[num].link[i]->loc.y()]=0;
    }
    game.ways[num].clearTail();
    this->update();
}

void GameInterface::cutWay(int num){
    clearWay(num);
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
                cutWay(game.map[a][b]);
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
                clearWay(game.nowWay);
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
    isTracking = 0;
    game.nowWay=0;
    for (int i=1;i<=game.waysTot;i++) game.ways[i].initWay();
    //exit(1);
    game.waysTot=0;
    for (int i=1;i<=game.gameFormat;i++)
        for (int j=1;j<=game.gameFormat;j++){
            game.blocks[i][j].initBlock();
        }

    makeBlocksInfo();
    makeSource();
}

void GameInterface::restartGame(){
    startGame();
}

void GameInterface::quitGame(){
    exit(0);
}

void GameInterface::makeBlocksInfo(){
    int len=game.getLen();
    for (int i=1;i<=game.gameFormat;i++)
        for (int j=1;j<=game.gameFormat;j++){
            game.blocks[i][j].rect=QRect(startY+len*(j-1),startX+len*(i-1),len,len);
            game.blocks[i][j].color=0;
            game.blocks[i][j].status=unmark;
            game.blocks[i][j].loc=QPoint(i,j);
            qDebug()<<i<<" "<<j<<" "<<"color: "<<game.blocks[i][j].color<<game.blocks[i][j].rect;
        }

}

bool GameInterface::isLegal(){
    if (game.sourceTot>myColorTot){
        qDebug()<<"color not enough...";
        exit(0);
    }
    return true;
}

void GameInterface::makePos(int &x,int &y){
    do{
        x=qrand()%game.gameFormat+1,y=qrand()%game.gameFormat+1;
    }while(game.blocks[x][y].status == source);
}

int markColor[myColorTot+5];
void GameInterface::makeColor(int &color){
    do{
        color=qrand()%(myColorTot-1)+1;
    }while(markColor[color]);
    markColor[color]=1;

}

void GameInterface::makeSource(){
    do{
        game.sourceTot=3;
        for (int i=1;i<=game.sourceTot;i++){
            int x,y,x2,y2,color;
            makePos(x,y);
            makePos(x2,y2);
            makeColor(color);
            game.blocks[x][y].status = source;
            game.blocks[x][y].color=color;
            game.blocks[x2][y2].status = source;
            game.blocks[x2][y2].color=color;
        }
    }while (!isLegal());
    game.waysTot=0;
    for (int i=1;i<=game.gameFormat;i++)
        for (int j=1;j<=game.gameFormat;j++){
            if (game.blocks[i][j].status == source){
                game.ways[++game.waysTot].link.clear();
                game.ways[game.waysTot].add(&game.blocks[i][j]);
                game.map[i][j]=game.waysTot;
            }
        }
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
        quitGame();
    }
}

GameInterface::GameInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameInterface)
{
    ui->setupUi(this);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    game.gameFormat = 7;
    drawer = new Drawer(this,&game);

    startGame();
}

GameInterface::~GameInterface()
{
    delete ui;
}




