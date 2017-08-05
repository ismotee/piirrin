#pragma once
#include "Viiva.h"
#include "Hiiri.h"
#include "hidpen.h"
#include "Sessio.h"
#include "timedThread.h"
#include "ViivanOhjain.h"
#include "Nauhuri.h"

enum OhjainTila {vapaa,tallentaa,soittaa};

struct ViivanOhjain: public Sessio, public Hiiri, public Nauhuri {
    Viiva viiva;
    std::string viivaStr;
    OhjainTila tila;
    
    bool viivaOnUusi;
    
    string kerroTila() {if(tila == vapaa)return "vapaa";if(tila == tallentaa)return "tallentaa";if(tila==soittaa)return "soittaa";}
    
    void setup(int viivaKesken);
    void loop();
    
    
    void lisaaPiste(ofPoint piste, float paine);
    void tyhjenna();

    void tulkitseUusinPiste();
    void laskeUusinPiste();
    Viiva haeViiva();

    float laskeKeskinopeus(int otanta);
    float laskeKeskipaine(int otanta);

    float bound(float val, float min, float max) {
        if (val > max)
            return max;
        else if (val < min)
            return min;
        return val;
    }



};

