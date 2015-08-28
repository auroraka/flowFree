#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include "gameinfo.h"
#include "drawer.h"
#include "textinfo.h"
#include "chooseinterface.h"
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
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void startGame();
    void quitGame();
    bool checkGameComplete();
    void gameComplete();
    bool checkGameFinishHalf();
    void gameFinishHalf();
    void connectTextInfo(QWidget *choose);
    void showLevel();
    bool isTracking;
    int focusWay;

private slots:
    //void on_action_triggered();

    void on_back_button_clicked();

    void on_previous_level_button_clicked();

    void on_next_level_button_clicked();

    void on_restart_button_clicked();

    void on_save_button_clicked();

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
    int level,id;
    void cheat();

public slots:
    void getTextInfo(TextInfo text,int level,int id);
    void nextLevel();
    void previousLevel();
    void restartGame();
    void keepGame();

private:
    Ui::GameInterface *ui;
    GameInfo game;
    Drawer *drawer;
    QString cheatRecord;
    int wayConnectEvent;
};

#endif // GAMEINTERFACE_H
