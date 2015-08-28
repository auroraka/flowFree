#include "music.h"


#include <QTextStream>
#include <QDebug>
#include <QFileInfo>

Music::Music()
{
    status=Open;
    loadMusic();
    QFileInfo file("background.wav");
    if (file.exists()){
        background = new QSound("background.wav");
    }else{
        background = new QSound(":/music/music/background.wav");
    }
    background->setLoops(QSound::Infinite);
    background->play();
}

void Music::changeStatus(){
    if (status == Open){
        status = Close;
        background->stop();

    }else{
        status = Open;
        background->play();
    }
}

MusicStatus Music::getStatus(){
    return status;
}

QString loadMusicList[]={
    "cheaton",
    "gameComplete",
    "gameFinishHalf",
    "menuback",
    "menuclick",
    "waybreak",
    "wayconnect",
};
int musicTot=7;


void Music::loadMusic(){
    for (int i=0;i<musicTot;i++){
        QString fileDir;
        QTextStream(&fileDir)<<":/music/music/"<<loadMusicList[i]<<".wav";
        qDebug()<<"openMusic: "<<fileDir;
        musicList[loadMusicList[i]]=fileDir;
    }
}

void Music::playMusic(QString name){
    if (status == Close) return;
    if (musicList.find(name) == musicList.end()){
        qDebug()<<"[ERROR] music not found: "<<name;
        return;
    }
    qDebug()<<"play music: "<<name;
    QSound::play(musicList[name]);
}
