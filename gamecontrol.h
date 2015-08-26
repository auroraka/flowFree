#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "way.h"
#include "block.h"
#include <QMainWindow>

namespace Ui {
class GameControl;
}

class GameControl : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameControl(QWidget *parent = 0);
    ~GameControl();
    //Event
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void drawGridding();
    void drawBlocks();
    void drawWays();
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
    void on_action_triggered();

private:
    void makeBlocksInfo();
    bool isLegal();
    void makeSource();
    void makeColor(int &color);
    void makePos(int &x,int &y);
    void cutWay(int num);
    void clearWay(int num);

private:
    Ui::GameControl *ui;
    Block blocks[15][15];
    int map[15][15];
    Way ways[50];
    int waysTot;
    int sourceTot;
    int nowWay;

};

#endif // MAINWINDOW_H
