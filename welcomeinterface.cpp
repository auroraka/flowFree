#include "welcomeinterface.h"
#include "enviroment.h"
#include "switcher.h"
#include "music.h"
#include "ui_welcomeinterface.h"
#include "settingform.h"
#include "textinfo.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

//static Switcher switcher;

WelcomeInterface::WelcomeInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeInterface)
{
    ui->setupUi(this);
    this->hide();

    //添加背景
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/picture/picture/background.jpg")));
    this->setPalette(palette);

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
    QUrl url = QFileDialog::getOpenFileUrl(this,"打开游戏存档",QUrl("/"),"(*.bak)");
    qDebug()<<"open file: "<<url.path();
    TextInfo text;
    text.openFile(url.path().remove(0,1));
    GameInfo game;
    if (!text.transToGameInfo(game)){
        QMessageBox::warning(this,"错误","非法的游戏存档",QMessageBox::Abort);
        return;
    }
    emit sendTextInfo(text,game.gameFormat,0);
    switcher.showInterface("game");


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


void WelcomeInterface::on_exit_button_clicked()
{
    exit(0);
}
