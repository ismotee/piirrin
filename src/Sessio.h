#pragma once

#include "ofMain.h"
#include "Hiiri.h"


enum Moodi {piirtaa,viivaValmis};

/*
struct Hiiri {
    ofPoint mouseState;
    bool click;
    void moved(float x,float y) {mouseState = ofPoint(x,y,mouseState.z);}
    void released(float x,float y){mouseState = ofPoint(x,y,0);}
    void pressed(float x, float y){mouseState = ofPoint(x,y,1);click = true;}
    
};
*/

class Sessio {
public:

    Hiiri hiiri;
    int updateCount,viivaKeskenCount;
    
    
    void setup(int viivaKeskenCount_);
    void update();
    
    Moodi moodi;
    
    
private:

};
