#pragma once
#include "Viiva.h"
struct ViivanOhjain {
    Viiva viiva;
    std::string viivaStr;
    
    
    void lisaaPiste(ofPoint piste, float paine);
    void tyhjenna();
    
    
};

