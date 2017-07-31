#include "Sessio.h"

void Sessio::setup(int viivaKeskenCount_) {
    viivaKeskenCount = viivaKeskenCount_;
    updateCount = 0;
}

void Sessio::update() // valitaan moodi joka kierroksella
{

    if (hiiri.mouseState.z) {
        moodi = piirtaa;
        updateCount = 0;
    } else {
        updateCount++;
        if (updateCount > viivaKeskenCount) {
            moodi = viivaValmis;
        }
    }
}

