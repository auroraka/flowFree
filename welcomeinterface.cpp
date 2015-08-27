#include "welcomeinterface.h"
#include "enviroment.h"
#include "switcher.h"
#include "ui_welcomeinterface.h"
#include "settingform.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

//static Switcher switcher;

WelcomeInterface::WelcomeInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeInterface)
{
    ui->setupUi(this);
}

WelcomeInterface::~WelcomeInterface()
{
    delete ui;
}

void WelcomeInterface::on_goIntoGame_button_clicked()
{
    switcher.showInterface("choose");
}

void WelcomeInterface::on_designGame_button_clicked()
{
    switcher.showInterface("design");
}


void WelcomeInterface::on_loadGame_button_clicked()
{
    QUrl url = QFileDialog::getOpenFileUrl(this,"打开游戏存档");
    qDebug()<<"open file: "<<url.path();
}

void WelcomeInterface::on_setting_button_clicked()
{
    SettingForm setting(this);
    setting.exec();
}

void WelcomeInterface::on_help_button_clicked()
{
    QString info;
    QTextStream(&info)
        <<"Drag to connect matching colors with pipe,creating a flow\n"
        <<"Pair all colors, and cover the entire board with pipe to solve\n"
        <<"each puzle.\n"
        <<"\n"
        <<"But watch out, pipes will break if they cross or overlap!\n"
        <<"\n"
        <<"Too easy? Try selecting a larger board or different level pack.\n"
        <<"Or see how fast you can solve in Time Trial mode.\n"
        ;
    QMessageBox::about(this,"Flow Free",info);
}
