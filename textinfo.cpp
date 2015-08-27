#include "textinfo.h"
#include "enviroment.h"
#include <QTextStream>
#include <QFile>
#include <QDebug>

TextInfo::TextInfo(){

}

TextInfo::TextInfo(const GameInfo &game)
{
    gameFormat = game.gameFormat;
    for (int i=1;i<=gameFormat;i++)
        for (int j=1;j<=gameFormat;j++){
            if (game.blocks[i][j].status == unmark){
                map[i][j]=0;
            }
            if (game.blocks[i][j].status == source){
                map[i][j] =game.blocks[i][j].color;
            }
            if (game.blocks[i][j].status == gothrough){
                map[i][j] = -game.blocks[i][j].color;
            }
        }
}


bool TextInfo::openFile(QString fileDir){
    QFile *file = new QFile(fileDir);

    if (file->open(QFile::ReadOnly | QFile::Text))
    {
        file->deleteLater();
        QByteArray buff = file->readAll();
        QTextStream stream( &buff );
        stream.setCodec("UTF-8");

        stream>>gameFormat;
        for (int i=1;i<=gameFormat;i++)
            for (int j=1;j<=gameFormat;j++)
                stream>>map[i][j];
    }else
    {
        qDebug()<<"no file in dir:"<<fileDir;
        return false;
    }
    return true;
}


bool TextInfo::saveFile(QString fileDir){
    QFile *file = new QFile(fileDir);

    if (file->open(QFile::WriteOnly | QFile::Text))
    {
        file->deleteLater();
        QTextStream stream(file);
        stream.setCodec("UTF-8");
        stream<<gameFormat<<endl;
        for (int i=1;i<=gameFormat;i++){
            for (int j=1;j<=gameFormat;j++){
                stream<<map[i][j]<<" ";
            }
            stream<<endl;
        }
    }else{
        qDebug()<<"open file fail";
        return false;
    }
    return true;
}

bool TextInfo::inMap(int x,int y){
    return 1<=x&&x<=gameFormat&&1<=y&&y<=gameFormat;
}

int colorTot[maxColorTot];
int visit[maxColorTot][maxColorTot];


bool TextInfo::dfs(int x,int y,int num,GameInfo &game){
    int tot=0,haveEnd=0;
    for (int i=0;i<4;i++){
        int nx=x+xo[i];
        int ny=y+yo[i];
        if (inMap(nx,ny)){
            if (!visit[nx][ny] && abs(map[x][y]) == abs(map[nx][ny])){
                tot++;
                visit[nx][ny]=1;
                if (map[nx][ny]<0){
                    game.blocks[nx][ny].status = gothrough;
                    game.blocks[nx][ny].color = abs(map[nx][ny]);
                    game.ways[num].add(&game.blocks[nx][ny]);
                    game.map[nx][ny]=num;
                    if (!dfs(nx,ny,num,game)){
                        return false;
                    }else{
                        haveEnd=1;
                    }
                }
                if (map[nx][ny]>0){
                    game.ways[num].add(&game.blocks[nx][ny]);
                    haveEnd=1;
                }
            }
        }
    }
    return tot<=2&&haveEnd;
}

bool TextInfo::checkColorLegal(){
    for (int i=1;i<=myColorTot;i++) if (!(colorTot[i]==0||colorTot[i]==2)){
        qDebug()<<"[ERROR] color number ilegal "<<myColor[i]<<": "<<colorTot[i];
        return false;
    }
    return true;
}

bool TextInfo::checkWaysLegal(const GameInfo &game){
    for (int i=1;i<=myColorTot;i++) colorTot[i]=0;
    for (int i=1;i<=game.waysTot;i++){
        if (game.ways[game.waysTot].size()>1) colorTot[game.ways[game.waysTot].getColor()]++;
    }
    for (int i=1;i<=myColorTot;i++) if (colorTot[i]>=2){
        qDebug()<<"[ERROR] ways ilegal";
        return false;
    }
    return true;
}

bool TextInfo::haveGothrough(int x,int y){
    int count=0;
    for (int i=0;i<4;i++){
        int nx=x+xo[i];
        int ny=y+yo[i];
        if (inMap(nx,ny)){
            if (map[nx][ny]<0) count++;
        }
    }
    return count>0;
}

bool TextInfo::transToGameInfo(GameInfo &game){
    game.reInit();
    for (int i=1;i<=gameFormat;i++)
        for (int j=1;j<=gameFormat;j++)
            visit[i][j]=0;
    for (int i=1;i<=myColorTot;i++) colorTot[i]=0;
    game.gameFormat = gameFormat;
    game.sourceTot = 0;
    game.waysTot =0;
    game.nowWay =0;
    for (int i=1;i<=gameFormat;i++)
        for (int j=1;j<=gameFormat;j++){
            if (map[i][j]==0){
                game.blocks[i][j].status=unmark;
            }
            if (map[i][j]>0){
                colorTot[map[i][j]]++;

                game.blocks[i][j].status=source;
                game.blocks[i][j].color=map[i][j];
                game.sourceTot ++;
                game.waysTot ++;
                game.ways[game.waysTot].add(&game.blocks[i][j]);
                game.map[i][j]=game.waysTot;

                if (haveGothrough(i,j)&&!dfs(i,j,game.waysTot,game)) return false;
            }
        }

    if (!checkColorLegal()) return false;
    if (!checkWaysLegal(game)) return false;
    for (int i=1;i<=gameFormat;i++)
        for (int j=1;j<=gameFormat;j++){
            if (map[i][j]<0 && !visit[i][j]){
                qDebug()<<"[ERROR] ilegal";
                return false;
            }
        }
    for (int i=1;i<=gameFormat;i++)
        for (int j=1;j<=gameFormat;j++)
            game.blocks[i][j].loc=QPoint(i,j);
    return true;
}
bool TextInfo::loadGame(int level,int id){
    QString fileDir;
    QTextStream(&fileDir)<<":/level/level/"<<level<<"/"<<level<<"-"<<id<<".bak";
    return openFile(fileDir);

}

void TextInfo::print(){
    qDebug()<<"-----TextInfo print-----";
    qDebug()<<gameFormat;
    for (int i=1;i<=gameFormat;i++){
        QString line;
        QTextStream stream(&line);
        for (int j=1;j<=gameFormat;j++){
          stream<<map[i][j]<<" ";
        }
        stream<<endl;
        qDebug()<<line;
    }
    qDebug()<<"------------------------";
}
