#ifndef MUSIC_H
#define MUSIC_H

#include <QSound>
#include <map>
using std::map;

enum MusicStatus{Open=0,Close=1};

class Music
{
public:
    Music();
    void changeStatus();
    void loadMusic();
    void playMusic(QString name);
    MusicStatus getStatus();

private:
    MusicStatus status;
    map<QString,QString> musicList;
    QSound *background;
};

extern Music music;
#endif // MUSIC_H
