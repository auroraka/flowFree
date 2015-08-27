#ifndef MUSIC_H
#define MUSIC_H

enum MusicStatus{Open=0,Close=1};

class Music
{
public:
    Music();
    void changeStatus();
    void loadMusic();

private:
    MusicStatus status;
};

extern Music music;
#endif // MUSIC_H
