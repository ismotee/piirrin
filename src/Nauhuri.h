#pragma once
#include "ofMain.h"
#include "Viiva.h"
#include "tiedosto.h"


struct Nauhuri {
    bool uusiViiva;
    int viivaId;
    float lukuPaa;
    bool paused;
    ofDirectory dir;
    std::string polku;
    
    std::vector<Viiva> db;
    
    void setup(std::string polku_);
    
    void lataa();
    void tallenna(Viiva viiva);
    ViivanPiste soita();
    void pause();

    void seuraava();
    void edellinen();
};
