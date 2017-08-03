#pragma once
#include "ofMain.h"
#include "Viiva.h"

enum NauhurinTila {soittaa,nauhoittaa};

struct nauhuri {
    NauhurinTila tila;
    Viiva nykyinenViiva;
    float lukuPaa;
    bool paused;
    ofDirectory dir;
    std::string polku;
    
    std::vector<Viiva> db;
    
    void setup(std::string polku_);
    
    void lataa();
    void tallenna();
    void soita();
    void pause();

    void asetaNykyinenViiva(Viiva viiva);
    void seuraava();
    void edellinen();
};
