#include "gameinterface.h"
#include "welcomeinterface.h"
#include "designinterface.h"
#include "chooseinterface.h"
#include "switcher.h"
#include "music.h"
#include "enviroment.h"
#include "settingform.h"
#include <QApplication>
#include <QDebug>
#include <QTime>

Switcher switcher;
Music music;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));


    static DesignInterface design;
    static WelcomeInterface welcome;
    static GameInterface game;
    static ChooseInterface choose;
    game.connectTextInfo(&choose);

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
    return a.exec();
}
