#include "chooseform.h"
#include "ui_gamecontrol.h"
#include "enviroment.h"
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

int gameFormat=5;

int getLen(){
    return Height/gameFormat;
}


//------------------------drawPart------------------------------
void GameControl::drawGridding(){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen *pen = new QPen(QColor(210,113,4));
    pen->setWidth(penLen);
    painter.setPen(*pen);
    int len=getLen();
    for (int i=0;i<=gameFormat;i++){
        painter.drawLine(QPoint(startX+i*len,startY),QPoint(startX+i*len,startY+Height));
    }
    for (int i=0;i<=gameFormat;i++){
        painter.drawLine(QPoint(startX,startY+i*len),QPoint(startX+Weight,startY+i*len));
    }
}

void GameControl::drawBlocks(){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    for (int i=1;i<=gameFormat;i++){
        for (int j=1;j<=gameFormat;j++){
            QColor color=myColor[blocks[i][j].color];
            QBrush brush(color);
            if (blocks[i][j].status != unmark){
                brush.setColor(QColor(color.red()*0.5,color.green()*0.5,color.blue()*0.5));
            }
            painter.setBrush(brush);
            //qDebug()<<i<<" "<<j<<" "<<blocks[i][j].rect;
            painter.drawRect(blocks[i][j].rect);

            //brush.setColor(color);
            //painter.setBrush(color);
            if (blocks[i][j].status == source){
                //qDebug()<<"source: "<<i<<" "<<j<<" "<<blocks[i][j].color;
                QPen pen(color);
                painter.setPen(pen);
                brush.setColor(color);
                painter.setBrush(brush);
                int len=30;
                QPoint pos=blocks[i][j].getCenter();
                painter.drawEllipse(pos.x()-len,pos.y()-len,len*2,len*2);
            }
        }
    }
}

void GameControl::drawWays(){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen;
    pen.setWidth(20);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::SquareCap);
    for (int i=1;i<=waysTot;i++) if (ways[i].size()>1){
        pen.setColor(myColor[ways[i].getColor()]);
        painter.setPen(pen);
        for (int j=1;j<ways[i].size();j++){
            //qDebug()<<"draw ways: "<<ways[i].link[j-1].loc<<"->"<<ways[i].link[j].loc<<" color: "<<ways[i].link[j-1].color<<" "<<ways[i].link[j].color;
            painter.drawLine(ways[i].link[j-1]->getCenter(),ways[i].link[j]->getCenter());
        }
    }
}


void GameControl::paintEvent(QPaintEvent *event){
    static int times = 0;
    //qDebug()<<"Draw again."<<times++<<gameFormat;
    drawBlocks();
    drawGridding();
    drawWays();
}


//------------------------gameEvent-----------------------


int mapPos(int x,int y,int &a,int &b){
   a=(y-startX)/getLen()+1;
   b=(x-startY)/getLen()+1;
}


void GameControl::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && !nowWay){
        int a,b;
        mapPos(event->x(),event->y(),a,b);
        qDebug()<<"mouse press: "<<a<<" "<<b;
        if (blocks[a][b].status == source){
            isTracking = 1;
            nowWay = map[a][b];
            for (int i=1;i<=waysTot;i++) if (ways[i].getColor() == blocks[a][b].color){
                ways[i].clearTail();
            }
        }
        this->update();
    }
}
void GameControl::clearWay(int num){
    for (int i=1;i<ways[num].link.size();i++){
        map[ways[num].link[i]->loc.x()][ways[num].link[i]->loc.y()]=0;
    }
    ways[num].clearTail();
    this->update();
}

void GameControl::cutWay(int num){
    clearWay(num);
}

void GameControl::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() == Qt::LeftButton && isTracking){
        //qDebug()<<"!";
        int a,b;
        mapPos(event->x(),event->y(),a,b);
        //qDebug()<<"mouse move: "<<a<<" "<<b<<" nowWay:"<<ways[nowWay].head().loc;
        if (blocks[a][b].isNeighbour(ways[nowWay].last())){
            if ( blocks[a][b].status == gothrough && blocks[a][b].color != ways[nowWay].getColor()){
                qDebug()<<"gothrough && color differrnt: "<<blocks[a][b].color<<" "<<ways[nowWay].getColor();
                cutWay(map[a][b]);
                qDebug()<<"cut way complete.";
            }
            //未标记点或终点
            if (blocks[a][b].status == unmark || (blocks[a][b].status == source && blocks[a][b].color == ways[nowWay].getColor() && !blocks[a][b].isSame(ways[nowWay].head()))){
                ways[nowWay].add(&blocks[a][b]);
                if (blocks[a][b].status == unmark){
                    blocks[a][b].status = gothrough;
                    blocks[a][b].color  = ways[nowWay].getColor();
                    map[a][b]=nowWay;
                }
          //      qDebug()<<"mark && size:"<<ways[nowWay].size();
                if (blocks[a][b].status == source){
                    nowWay=0;
                    isTracking=0;
                }
            }
        }
        this->update();
    }
}


void GameControl::mouseReleaseEvent(QMouseEvent *event){

    if (event->button() == Qt::LeftButton){
        if (isTracking){
            int a,b;
            mapPos(event->x(),event->y(),a,b);
            //到达终点合法,否则撤销已画路径
            if (blocks[a][b].status == source){
            }else{
                clearWay(nowWay);
            }
            isTracking = 0;
            nowWay = 0;
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

void GameControl::startGame(){
    isTracking = 0;
    nowWay=0;
    for (int i=1;i<=waysTot;i++) ways[i].initWay();
    waysTot=0;
    for (int i=1;i<=gameFormat;i++)
        for (int j=1;j<=gameFormat;j++){
            blocks[i][j].initBlock();
        }
    makeBlocksInfo();
    makeSource();
}

void GameControl::restartGame(){
    startGame();
}

void GameControl::quitGame(){
    exit(0);
}

void GameControl::makeBlocksInfo(){
    int len=getLen();
    for (int i=1;i<=gameFormat;i++)
        for (int j=1;j<=gameFormat;j++){
            blocks[i][j].rect=QRect(startY+len*(j-1),startX+len*(i-1),len,len);
            blocks[i][j].color=0;
            blocks[i][j].status=unmark;
            blocks[i][j].loc=QPoint(i,j);
            qDebug()<<i<<" "<<j<<" "<<"color: "<<blocks[i][j].color<<blocks[i][j].rect;
        }

}

bool GameControl::isLegal(){
    if (sourceTot>myColorTot){
        qDebug()<<"color not enough...";
        exit(0);
    }
    return true;
}

void GameControl::makePos(int &x,int &y){
    do{
        x=qrand()%gameFormat+1,y=qrand()%gameFormat+1;
    }while(blocks[x][y].status == source);
}

int markColor[myColorTot+5];
void GameControl::makeColor(int &color){
    do{
        color=qrand()%(myColorTot-1)+1;
    }while(markColor[color]);
    markColor[color]=1;

}

void GameControl::makeSource(){
    do{
        sourceTot=3;
        for (int i=1;i<=sourceTot;i++){
            int x,y,x2,y2,color;
            makePos(x,y);
            makePos(x2,y2);
            makeColor(color);
            blocks[x][y].status = source;
            blocks[x][y].color=color;
            blocks[x2][y2].status = source;
            blocks[x2][y2].color=color;
        }
    }while (!isLegal());
    waysTot=0;
    for (int i=1;i<=gameFormat;i++)
        for (int j=1;j<=gameFormat;j++){
            if (blocks[i][j].status == source){
                ways[++waysTot].link.clear();
                ways[waysTot].add(&blocks[i][j]);
                map[i][j]=waysTot;
            }
        }
}





//点击[选择游戏大小]
void GameControl::on_action_triggered()
{
    chooseForm *choose = new chooseForm(0);
    choose->exec();
    this->update();
    restartGame();
}

bool GameControl::checkGameComplete(){
    for (int i=1;i<=gameFormat;i++)
        for (int j=1;j<=gameFormat;j++){
            if (blocks[i][j].status == unmark){
                return false;
            }
        }
    return true;
}

void GameControl::gameComplete(){
    int ret = QMessageBox::question(0,"恭喜你","是否再来一局?",QMessageBox::Yes,QMessageBox::No);
    if (ret == QMessageBox::Yes){
        restartGame();
    }else{
        quitGame();
    }
}

bool GameControl::checkGameFinishHalf(){
    int count=0;
    for (int i=1;i<=waysTot;i++) if (ways[i].size()>1){
        count++;
    }
    qDebug()<<"game finish: "<<count<<" needed: "<<waysTot/2;
    return count>=waysTot/2;
}

void GameControl::gameFinishHalf(){
    int ret = QMessageBox::question(0,"已经完成一半了","继续?",QMessageBox::Yes,QMessageBox::No);
    if (ret == QMessageBox::Yes){

    }else{
        quitGame();
    }
}

GameControl::GameControl(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameControl)
{
    ui->setupUi(this);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    //centralWidget()->setMouseTracking(true);
    startGame();
}

GameControl::~GameControl()
{
    delete ui;
}




