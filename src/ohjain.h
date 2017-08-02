#pragma once

#include "ofMain.h"
#include "OscInterface.h"
#include "GUI.h"
#include "ViivanOhjain.h"
#include "VariOhjain.h"

struct Ohjain: public OscInterface, public ViivanOhjain, public VariOhjain {
    GUI gui;

    Viiva uusinViiva;
    ofColor uusinVari;
    
    void setup();
    void update();
    //void loop();
    void draw();
    void keyPressed(int key);
    
    void mousePressed(int x, int y);
};


