#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "block.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void drawBackground();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void changeBlock(int pox,int posy,QColor color);

private slots:
    void on_action_triggered();

private:
    void makeBlocksInfo();
    void initGame();

private:
    Ui::MainWindow *ui;
    Block blocks[15][15];
};

#endif // MAINWINDOW_H
