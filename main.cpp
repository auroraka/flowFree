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

Switcher switcher;
Music music;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    static DesignInterface design;
    static WelcomeInterface welcome;
    static GameInterface game;
    static ChooseInterface choose;

    switcher.add("design",&design);
    switcher.add("welcome",&welcome);
    switcher.add("game",&game);
    switcher.add("choose",&choose);

    switcher.showInterface("welcome");
    return a.exec();
}
