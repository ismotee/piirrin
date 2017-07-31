#pragma once

#include "ofMain.h"
#include "OscInterface.h"
#include "hidpen.h"
#include "Hiiri.h"
#include "GUI.h"
#include "Sessio.h"
#include "timedThread.h"
#include "ViivanOhjain.h"

struct Ohjain: public OscInterface, public Sessio, public timedThread {
    GUI gui;
    ViivanOhjain vOhjain;
    
    
    void setup();
    void update();
    void loop();
    void draw();
    void keyPressed(int key);
    
    void mousePressed(int x, int y);
    
};


