#include "gameinterface.h"
#include "welcomeinterface.h"
#include "designinterface.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //DesignInterface design;
    //design.show();
    //WelcomeInterface welcome;
    //welcome.show();
    //welcome.hide();
    GameInterface game;
    //game.setVisible(false);
    game.show();
    return a.exec();
}
