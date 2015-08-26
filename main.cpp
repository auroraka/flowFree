#include "gamecontrol.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameControl game;
    game.show();
    return a.exec();
}
