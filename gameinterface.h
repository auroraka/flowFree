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
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void startGame();//开始游戏
    void quitGame();//离开游戏
    bool checkGameComplete();//检查游戏完成
    void gameComplete();//游戏完成
    bool checkGameFinishHalf();//检查游戏完成(未填满)
    void gameFinishHalf();//游戏完成(未填满)
    void connectTextInfo(QWidget *choose);
    void showLevel();//显示当前关卡标签

private slots:
    void on_back_button_clicked();//"Exit"按钮事件
    void on_previous_level_button_clicked();//"上一关"按钮事件
    void on_next_level_button_clicked();//"下一关"按钮事件
    void on_restart_button_clicked();//"重来"按钮事件
    void on_save_button_clicked();//"保存游戏"按钮事件

    void on_pushButton_clicked();

    void on_lineEdit_editingFinished();

private:
    int level,id;//处于第level-id关
    void cheat();//作弊模式开启

public slots:
    void getTextInfo(TextInfo text,int level,int id);//接收传来的游戏信息
    void nextLevel();//下一关
    void previousLevel();//上一关
    void restartGame();//重新开始游戏
    void keepGame();

private:
    Ui::GameInterface *ui;
    GameInfo game;
    Drawer *drawer;
    QString cheatRecord;
    QString godRecord;
    int wayConnectEvent;
};

#endif // GAMEINTERFACE_H
