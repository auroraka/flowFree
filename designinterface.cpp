#include "designinterface.h"
#include "switcher.h"
#include "enviroment.h"
#include "ui_designinterface.h"
#include "textinfo.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

DesignInterface::DesignInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DesignInterface)
{
    ui->setupUi(this);
    this->hide();
    drawer  = new Drawer(this,&game);
}

DesignInterface::~DesignInterface()
{
    delete ui;
}

void DesignInterface::paintEvent(QPaintEvent *event){
    drawer->painter = new QPainter(this);
    drawer->draw();
    int nowColor=0;
    for (int i=1;i<=2;i++)
        for (int j=1;j<=4;j++){
            nowColor++;
            drawer->drawSource(myColor[nowColor],QPoint(selectionStartX+i*selectionLen,selectionStartY+j*selectionLen));
        }
    if (haveMovePoint){
        qDebug()<<"draw movePoint: "<<movePoint;
        drawer->drawSource(myColor[sourceColor],movePoint);
    }
}

bool inBox(QPoint now,QPoint pos){
    int len=sourceWide;
    qDebug()<<"check inBox: "<<now<<" "<<pos<<" "<<
              bool(pos.x()-len<=now.x() && now.x()<=pos.x()+len
              &&pos.y()-len<=now.y() && now.y()<=pos.y()+len);
    return pos.x()-len<=now.x() && now.x()<=pos.x()+len
         &&pos.y()-len<=now.y() && now.y()<=pos.y()+len;
}

void DesignInterface::mousePressEvent(QMouseEvent *event){
    qDebug()<<"design interface: mouse press "<<event->pos();
    if (event->button()!=Qt::LeftButton) return;
    int a,b;
    if (game.getLoc(a,b,event->pos())){
        if (game.blocks[a][b].status == source){
            game.blocks[a][b].status = unmark;
            game.blocks[a][b].color = 0;
        }
        this->update();
        return;
    }
    int nowColor=0;
    for (int i=1;i<=2;i++)
        for (int j=1;j<=4;j++){
            nowColor++;
            if (inBox(event->pos(),QPoint(selectionStartX+i*selectionLen,selectionStartY+j*selectionLen))){
                chooseSource=1;
                sourceColor=nowColor;
            }
        }
    this->update();
}
void DesignInterface::mouseMoveEvent(QMouseEvent *event){
    qDebug()<<"design interface: mouse move "<<event->pos();
    if (event->buttons()!=Qt::LeftButton) return;
    if (chooseSource){
        haveMovePoint=1;
        movePoint=event->pos();
    }
    this->update();
}

void DesignInterface::mouseReleaseEvent(QMouseEvent *event){
    qDebug()<<"design interface: mouse release "<<event->pos();
    if (event->button() != Qt::LeftButton) return;
    haveMovePoint=0;
    if (chooseSource){
        int a,b;
        if (game.getLoc(a,b,event->pos())){
            game.blocks[a][b].status=source;
            game.blocks[a][b].color=sourceColor;
        }
        chooseSource=0;
    }
    this->update();
}

void DesignInterface::reInit(){
    game.reInit();
    chooseSource=0;
    haveMovePoint=0;
}

void DesignInterface::on_back_button_clicked()
{
    switcher.showInterface("welcome");
    reInit();
    this->update();
}

void DesignInterface::on_radioButton_5_5_clicked()
{
    game.gameFormat=5;
    reInit();
    this->update();
}

void DesignInterface::on_radioButton_6_6_clicked()
{
    game.gameFormat =6;
    reInit();
    this->update();
}

void DesignInterface::on_radioButton_7_7_clicked()
{
    game.gameFormat=7;
    reInit();
    this->update();
}

void DesignInterface::on_store_button_clicked()
{
    if (!game.legalDesign()){
        QMessageBox::warning(this,"错误","您的设计有不合理的地方",QMessageBox::Abort);
        return;
    }
    QUrl url=QFileDialog::getSaveFileUrl(this,"保存到",QUrl("/"),"(*.bak)");
    qDebug()<<"store file :"<<url.path();
    TextInfo text(game);
    text.saveFile(url.path().remove(0,1));
}

void DesignInterface::on_clear_button_clicked()
{
    reInit();
    this->update();
}
