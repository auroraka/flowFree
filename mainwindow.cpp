#include "chooseform.h"
#include "ui_mainwindow.h"
#include "enviroment.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QInputDialog>
#include <QLabel>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QMessageBox>

int gameFormat=7;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    centralWidget()->setMouseTracking(true);
    initGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int getLen(){
    return Height/gameFormat;
}

static int blockTimes=0;
void MainWindow::makeBlocksInfo(){
    qDebug()<<"make blocks info "<<blockTimes++;
    int len=getLen();
    for (int i=1;i<=gameFormat;i++)
        for (int j=1;j<=gameFormat;j++){
            blocks[i][j]=Block(QRect(startX+len*(i-1),startY+len*(j-1),len,len),QColor(Qt::black));
            //qDebug()<<i<<" "<<j<<" "<<"color: "<<blocks[i][j].color<<blocks[i][j].rect;
        }

}

void MainWindow::initGame(){
    makeBlocksInfo();
}

void MainWindow::drawBackground(){
    /*QPainter painter(this);
    QBrush brush(Qt::black);
    painter.setBrush(brush);
    painter.drawRect(QRect(startX+penLen,startY+penLen,Height-2*penLen-1,Weight-2*penLen-1));

    QPen *pen = new QPen(QColor(210,113,4));
    pen->setWidth(penLen);
    painter.setPen(*pen);
    int len=Height/gameFormat;
    for (int i=0;i<=gameFormat;i++){
        painter.drawLine(QPoint(startX+i*len,startY),QPoint(startX+i*len,startY+Height));
    }
    for (int i=0;i<=gameFormat;i++){
        painter.drawLine(QPoint(startX,startY+i*len),QPoint(startX+Weight,startY+i*len));
    }*/
    QPainter painter(this);
    for (int i=1;i<=gameFormat;i++){
        for (int j=1;j<=gameFormat;j++){
            QBrush brush(blocks[i][j].color);
            painter.setBrush(brush);
            painter.drawRect(blocks[i][j].rect);
        }
    }

    QPen *pen = new QPen(QColor(210,113,4));
    pen->setWidth(penLen);
    painter.setPen(*pen);
    int len=getLen();
    for (int i=0;i<=gameFormat;i++){
        painter.drawLine(QPoint(startX+i*len,startY),QPoint(startX+i*len,startY+Height));
    }
    for (int i=0;i<=gameFormat;i++){
        painter.drawLine(QPoint(startX,startY+i*len),QPoint(startX+Weight,startY+i*len));
    }
}

void MainWindow::paintEvent(QPaintEvent *event){
    static int times = 0;
    //qDebug()<<"Draw again."<<times++<<gameFormat;
    drawBackground();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    QString info;
    QTextStream(&info)<<"("<<event->x()-startX<<","<<event->y()-startY<<")";
    statusBar()->showMessage(info);
}

void MainWindow::changeBlock(int posx,int posy,QColor color){
    qDebug()<<"block change: "<<posx<<" "<<posy<<" "<<color;
    blocks[posx][posy].color = color;
    this->update();
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    int len=Weight/gameFormat;
    QString info;
    int posx=((event->y()-startY)/len)+1,posy=((event->x()-startX)/len)+1;
    if (!(1<=posx&&posx<=gameFormat)||!(1<=posy&&posy<=gameFormat)){
        QMessageBox::about(this,"您所点击的区域是","游戏区域外");
        return;
    }
    qDebug()<<"pos: "<<event->x()-50<<" "<<event->y()-50<<" len:"<<len;
    QTextStream(&info)<<tr("第 ")<<posx<<tr(" 行\n第 ")<<posy<<tr(" 列");
    QMessageBox::about(this,"您所点击的区域是",info);
    changeBlock(posy,posx,QColor(205,205,205));
}

#include <QDebug>
void MainWindow::on_action_triggered()
{
    chooseForm *choose = new chooseForm(0);
    choose->exec();
    this->update();
    makeBlocksInfo();
    //this->repaint();
}

