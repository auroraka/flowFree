#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include "gameinfo.h"
#include "drawer.h"
#include <QMainWindow>

namespace Ui {
class GameInterface;
}

class GameInterface : public QWidget
{
    Q_OBJECT

public:
    explicit GameInterface(QWidget *parent = 0);
    ~GameInterface();
    //Event
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void startGame();
    void restartGame();
    void quitGame();
    bool checkGameComplete();
    void gameComplete();
    bool checkGameFinishHalf();
    void gameFinishHalf();
    bool isTracking;
    int focusWay;

private slots:
    //void on_action_triggered();

private:
    void makeBlocksInfo();
    bool isLegal();
    void makeSource();
    void makeColor(int &color);
    void makePos(int &x,int &y);
    void cutWay(int num);
    void clearWay(int num);
    int getLen();
    int mapPos(int x,int y,int &a,int &b);


private:
    Ui::GameInterface *ui;
    GameInfo game;
    Drawer *drawer;
};

#endif // GAMEINTERFACE_H
