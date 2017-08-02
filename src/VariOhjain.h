#pragma once
#include "ofMain.h"
#include "Viiva.h"

struct VariOhjain {
    ofColor vari;
    ViivanTulkinnat uusimmatTulkinnat;
    float hue, saturation, brightness;
    
    void setup();
    
    void laskeVari(Viiva& viiva);
    void laskeHue(Viiva& viiva);
    void laskeSaturation(Viiva& viiva);
    void laskeBrightness(Viiva& viiva);
    ofColor haeVari();
};