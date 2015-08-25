#include "chooseform.h"
#include "enviroment.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QRadioButton>
#include <QLabel>

chooseForm::chooseForm(QWidget *parent) : QDialog(parent)
{
    qDebug()<<"clicked";
    setWindowTitle("请选择游戏大小");
    QVBoxLayout *layout = new QVBoxLayout;
    radio5.setText("5*5");
    layout->addWidget(&radio5);

    radio6.setText("6*6");
    layout->addWidget(&radio6);

    radio7.setText("7*7");
    layout->addWidget(&radio7);

    radio8.setText("8*8");
    layout->addWidget(&radio8);

    radio9.setText("9*9");
    layout->addWidget(&radio9);

    radio10.setText("10*10");
    layout->addWidget(&radio10);

    radio11.setText("11*11");
    layout->addWidget(&radio11);

    radio12.setText("12*12");
    layout->addWidget(&radio12);

    QHBoxLayout *layoutH = new QHBoxLayout;
    button.setText("确定");
    layoutH->addLayout(layout);
    layoutH->addWidget(&button);

    setLayout(layoutH);
    setVisible(true);

    connect(&(this->button),SIGNAL(clicked(bool)),this,SLOT(chooseDone()));
}

void chooseForm::chooseDone(){
    if (radio5.isChecked()) gameFormat=5;
    if (radio6.isChecked()) gameFormat=6;
    if (radio7.isChecked()) gameFormat=7;
    if (radio8.isChecked()) gameFormat=8;
    if (radio9.isChecked()) gameFormat=9;
    if (radio10.isChecked()) gameFormat=10;
    if (radio11.isChecked()) gameFormat=11;
    if (radio12.isChecked()) gameFormat=12;
    if (gameFormat<5 || gameFormat >12) gameFormat =7;
    qDebug()<<"gameFormat changeed:" <<gameFormat;
    setVisible(false);
}
