#include "solution.h"
#include "enviroment.h"
#include "textinfo.h"
#include <QDebug>
#include <QTextStream>

Solution::Solution()
{

}
void Solution::greedyAlgorithm(){

}
bool Solution::inMap(int x,int y){
    return 1<=x&&x<=game.gameFormat && 1<=y&&y<=game.gameFormat;
}

bool Solution::fillAll(){
    for (int i=1;i<=game.gameFormat;i++){
        for (int j=1;j<=game.gameFormat;j++){
            if (game.blocks[i][j].status == unmark) return false;
        }
    }
    return true;
}

bool Solution::dfs(int colorID,QPoint pos,int step){
    record[step]=pos;
    for (int k=0;k<4;k++){
        int nx=pos.x()+xo[k];
        int ny=pos.y()+yo[k];
        if (inMap(nx,ny)){
            if (game.blocks[nx][ny].status == source && QPoint(nx,ny)==pointRecord[colorID][1]){
                //qDebug()<<"one way find: "<<colorID<<": "<<pointRecord[colorID][0]<<"->"<<pointRecord[colorID][1]<<" ("<<pos<<"->"<<QPoint(nx,ny)<<")  status:"<<game.blocks[pos.x()][pos.y()].status;
                if (colorID == game.sourceTot/2 && fillAll()){
                    QString info;
                    QTextStream stream(&info);
                    for (int i=1;i<=step;i++){
                        stream<<"("<<record[i].x()<<","<<record[i].y()<<") ";
                    }
                    qDebug()<<info;
                    TextInfo text(game);
                    qDebug()<<"find answer.";
                    text.print();
                    return true;
                }else{
                    return dfs(colorID+1,pointRecord[colorID+1][0],step+1);
                }
            }else if (game.blocks[nx][ny].status == unmark){
                game.blocks[nx][ny].status = gothrough;
                game.blocks[nx][ny].color = colorRecord[colorID];
                if (dfs(colorID,QPoint(nx,ny),step+1)) return true;
                game.blocks[nx][ny].status = unmark;
                game.blocks[nx][ny].color = 0;
            }
        }
    }
    return false;
}

TextInfo Solution::getSolution(const GameInfo &oldGame){
    game=oldGame;
    game.restart();
    greedyAlgorithm();
    int count=2,pos=0;
    for (int color=1;color<=myColorTot;color++){
        if (count==2){
            count=0;
            pos++;
        }
        for (int i=1;i<=game.gameFormat;i++)
            for (int j=1;j<=game.gameFormat;j++) if (game.blocks[i][j].color == color && game.blocks[i][j].status == source){
                pointRecord[pos][count++]=QPoint(i,j);
                colorRecord[pos]=game.blocks[i][j].color;
            }
    }
    for (int i=1;i<=game.sourceTot/2;i++){
        qDebug()<<"color: "<<colorRecord[i]<<" "<<pointRecord[i][0]<<"->"<<pointRecord[i][1];
    }
    if (!dfs(1,pointRecord[1][0],1)){
        game.noSolution=1;
        qDebug()<<"no solution";
    }
    return TextInfo(game);
}
