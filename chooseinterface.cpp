#include "chooseinterface.h"
#include "switcher.h"
#include "enviroment.h"
#include "textinfo.h"
#include "ui_chooseinterface.h"
#include <QPainter>
#include <QTextStream>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>

ChooseInterface::ChooseInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseInterface)
{
    ui->setupUi(this);
    this->hide();
}


void ChooseInterface::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    for (int i=1;i<=5;i++){
        int id=5+i-1;

        QPen pen(myColor[i]);
        QFont font("Courier", 20);
        //font.setPointSize(20);
        painter.setPen(pen);
        painter.setFont(font);

        QString levelInfo;
        QTextStream(&levelInfo)<<id<<"*"<<id;
        painter.drawText(QPoint(30,startX+40+BlockLen*(i-1)),levelInfo);
        for (int j=1;j<=7;j++){
            painter.drawRect(QRect(startY+100+BlockLen*(j-1),startX+BlockLen*(i-1),BlockLen/3*2,BlockLen/3*2));
            painter.drawText(QPoint(startY+120+BlockLen*(j-1),startX+40+BlockLen*(i-1)),QString::number(j));
        }
    }
}
bool inBox(QPoint pos,QRect rect){
    return rect.x()<=pos.x() &&pos.x()<=rect.x()+rect.width()
         &&rect.y()<=pos.y() &&pos.y()<=rect.y()+rect.height();
}

bool getLoc(int &a,int &b,QPoint pos){
    for (int i=1;i<=5;i++)
        for (int j=1;j<=7;j++){
            if (inBox(pos,QRect(startY+100+BlockLen*(j-1),startX+BlockLen*(i-1),BlockLen/3*2,BlockLen/3*2))){
                a=i;b=j;
                return true;
            }
        }
    return false;
}

void ChooseInterface::loadGame(int level,int id){
    TextInfo text;
    if (text.loadGame(level,id)){
        emit sendTextInfo(text,level,id);
    }else{
        QMessageBox::information(this,"巨坑不填了","敬请期待新的关卡",QMessageBox::Yes);
        return;
    }
    switcher.showInterface("game");
}

void ChooseInterface::mousePressEvent(QMouseEvent *event){
    int level,id;
    if (!getLoc(level,id,event->pos())) return;
    level=level+5-1;
    qDebug()<<"clecked level: "<<level<<"-"<<id;
    loadGame(level,id);
}

ChooseInterface::~ChooseInterface()
{
    delete ui;
}

void ChooseInterface::on_back_button_clicked()
{
    switcher.showInterface("welcome");
}
