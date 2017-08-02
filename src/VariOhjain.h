#pragma once
#include "ofMain.h"
#include "Viiva.h"

struct VariOhjain {
    ofColor vari;
    ViivanTulkinnat uusimmatTulkinnat;
    
    
    void updateColor(ViivanTulkinnat& tulkinnat);
    void updateHue();
    void updateSaturation();
    void updateBrightness();
    
};