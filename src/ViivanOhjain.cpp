#include "ViivanOhjain.h"

void ViivanOhjain::lisaaPiste(ofPoint piste, float paine) {
    viiva.lisaaPiste(piste,paine);
    viiva.laske();
    viiva.tulkitse();
}

void ViivanOhjain::tyhjenna() {
    viiva = Viiva();
}
