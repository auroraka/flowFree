#include "music.h"

Music::Music()
{
    status=Open;
}

void Music::changeStatus(){
    if (status == Open){
        status = Close;
    }else{
        status = Open;
    }
}


void Music::loadMusic(){

}
