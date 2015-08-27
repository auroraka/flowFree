#include "textinfo.h"
#include "enviroment.h"

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


bool TextInfo::inMap(int x,int y){
    return 1<=x&&x<=gameFormat&&1<=y&&y<=gameFormat;
}

int colorTot[15];
int visit[15][15];


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
    for (int i=1;i<=myColorTot;i++) if (!(colorTot[i]==0||colorTot[i]==2)) return false;
    return true;
}

bool TextInfo::checkWaysLegal(const GameInfo &game){
    for (int i=1;i<=myColorTot;i++) colorTot[i]=0;
    for (int i=1;i<=game.waysTot;i++){
        if (game.ways[game.waysTot].size()>1) colorTot[game.ways[game.waysTot].getColor()]++;
    }
    for (int i=1;i<=myColorTot;i++) if (colorTot[i]>=2) return false;
    return true;
}

bool TextInfo::transToGameInfo(GameInfo &game){
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

                if (!dfs(i,j,game.waysTot,game)) return false;
            }
        }

    if (!checkColorLegal()) return false;
    if (!checkWaysLegal(game)) return false;
    for (int i=1;i<=gameFormat;i++)
        for (int j=1;j<=gameFormat;j++){
            if (map[i][j]<0 && !visit[i][j]){
                return false;
            }
        }
    return true;
}
