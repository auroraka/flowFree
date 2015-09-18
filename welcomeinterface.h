#ifndef WELCOMEINTERFACE_H
#define WELCOMEINTERFACE_H

#include "textinfo.h"
#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>

namespace Ui {
class WelcomeInterface;
}

class WelcomeInterface : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomeInterface(QWidget *parent = 0);
    ~WelcomeInterface();

signals:
    void sendTextInfo(TextInfo text,int level,int id);//将"载入游戏"读到的游戏存档发送给GameInterface处理
private slots:
    void on_goIntoGame_button_clicked();//"进入游戏"按钮事件
    void on_designGame_button_clicked();//"设计游戏"按钮事件
    void on_loadGame_button_clicked();//"载入游戏"按钮事件
    void on_setting_button_clicked();//"设置"按钮事件
    void on_help_button_clicked();//"帮助"按钮事件
    void on_exit_button_clicked();//"Exit"按钮事件
private:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);

    Ui::WelcomeInterface *ui;
};

#endif // WELCOMEINTERFACE_H
