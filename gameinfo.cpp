#include "gameinfo.h"
#include "enviroment.h"
#include "music.h"
#include "textinfo.h"
#include <QDebug>

GameInfo::GameInfo()
{
    waysTot=0;
    sourceTot=0;
    nowWay=0;
    gameFormat=5;
    makeBlocksInfo();
    noSolution=0;
}

void GameInfo::print(){
    TextInfo text(*this);
    text.print();
}

bool GameInfo::legalDesign(){
    int colorCount[maxColorTot];
    for (int i=0;i<myColorTot;i++) colorCount[i]=0;
    for (int i=1;i<=waysTot;i++) if (ways[i].size()>1) return false;
    for (int i=1;i<=gameFormat;i++)
        for (int j=1;j<=gameFormat;j++){
            colorCount[blocks[i][j].color]++;
        }
    for (int i=1;i<=myColorTot;i++) if (!(colorCount[i]==0||colorCount[i]==2)){
        qDebug()<<"color number ilegal: "<<myColor[i]<<" ->"<<colorCount[i];
        return false;
    }
    return true;
}
void GameInfo::restart(){
    for (int i=1;i<=waysTot;i++) ways[i].clearTail();
    for (int i=1;i<=gameFormat;i++)
        for (int j=1;j<=gameFormat;j++){
            if (blocks[i][j].status == gothrough) blocks[i][j].status = unmark;
            if (blocks[i][j].status != source){
                map[i][j]=0;
                blocks[i][j].color=0;
            }
        }
    nowWay=0;
}

void GameInfo::reInit(){
    nowWay=0;
    for (int i=1;i<=waysTot;i++) ways[i].initWay();
    waysTot=0;
    makeBlocksInfo();

}

void GameInfo::makeBlocksInfo(){
    qDebug()<<"make blocks info";
    for (int i=1;i<=gameFormat;i++)
        for (int j=1;j<=gameFormat;j++){
            blocks[i][j].color=0;
            blocks[i][j].status=unmark;
            blocks[i][j].loc=QPoint(i,j);
            //qDebug()<<"make blocks: "<<i<<" "<<j<<" "<<"color: "<<blocks[i][j].color<<blocks[i][j].getRect();
        }

}



//cutWay
void GameInfo::clearWay(int num){
    for (int i=1;i<ways[num].link.size();i++){
        map[ways[num].link[i]->loc.x()][ways[num].link[i]->loc.y()]=0;
    }
    ways[num].clearTail();
}

void GameInfo::cutWay(int num){
    music.playMusic("waybreak");
    clearWay(num);
}
//--------



//makeSource---
bool GameInfo::isLegal(){
    if (sourceTot>myColorTot){
        qDebug()<<"color not enough...";
        exit(0);
    }
    return true;
}

void GameInfo::makePos(int &x,int &y){
    do{
        x=qrand()%gameFormat+1,y=qrand()%gameFormat+1;
    }while(blocks[x][y].status == source);
}

int markColor[myColorTot+5];
void GameInfo::makeColor(int &color){
    do{
        color=qrand()%(myColorTot-1)+1;
    }while(markColor[color]);
    markColor[color]=1;

}

void GameInfo::makeSource(){
    qDebug()<<"make source";
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
//-----


bool GameInfo::getLoc(int &a,int &b,QPoint pos){
       a=(pos.y()-startX)/BlockLen+1;
       b=(pos.x()-startY)/BlockLen+1;
       if (!(1<=a&&a<=gameFormat&&1<=b&&b<=gameFormat)){
           a=0;
           b=0;
           return false;
       }
       return true;
}

