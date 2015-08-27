#include "gameinfo.h"
#include "enviroment.h"
#include <QDebug>

GameInfo::GameInfo()
{
    waysTot=0;
    sourceTot=0;
    nowWay=0;
    gameFormat=5;
    makeBlocksInfo();
}

int GameInfo::getLen(){
    return Height/gameFormat;
}


void GameInfo::makeBlocksInfo(){
    qDebug()<<"make blocks info";
    int len=getLen();
    for (int i=1;i<=gameFormat;i++)
        for (int j=1;j<=gameFormat;j++){
            blocks[i][j].rect=QRect(startY+len*(j-1),startX+len*(i-1),len,len);
            blocks[i][j].color=0;
            blocks[i][j].status=unmark;
            blocks[i][j].loc=QPoint(i,j);
            qDebug()<<"make blocks: "<<i<<" "<<j<<" "<<"color: "<<blocks[i][j].color<<blocks[i][j].rect;
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
