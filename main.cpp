#include "gameinterface.h"
#include "welcomeinterface.h"
#include "designinterface.h"
#include "chooseinterface.h"
#include "switcher.h"
#include "music.h"
#include "enviroment.h"
#include "settingform.h"
#include "database.h"
#include <QApplication>
#include <QDebug>
#include <QTime>
#include <QStyleFactory>

Switcher switcher;
Music music;
Database database;
int startX=30,startY=50;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));


    static DesignInterface design;
    static WelcomeInterface welcome;
    static GameInterface game;
    static ChooseInterface choose;
    game.connectTextInfo(&choose);
    game.connectTextInfo(&welcome);

    switcher.add("design",&design);
    switcher.add("welcome",&welcome);
    switcher.add("game",&game);
    switcher.add("choose",&choose);

    switcher.showInterface("welcome");
    welcome.setGeometry(100,100,welcome.width(),welcome.height());

    //Test---------
    //GameInterface game;
    //game.show();
    //-------------
    //a.setStyle(new QMac);
    return a.exec();
}
