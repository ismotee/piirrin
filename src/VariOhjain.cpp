
#include "VariOhjain.h"

void VariOhjain::setup() {
    vari = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
    hue = vari.getHue();
    saturation = vari.getSaturation();
    brightness = vari.getBrightness();
}

void VariOhjain::laskeVari(Viiva& viiva) {
    laskeHue(viiva);
    laskeSaturation(viiva);
    laskeBrightness(viiva);

    vari.setHsb(hue, saturation, brightness);
}

void VariOhjain::laskeHue(Viiva& viiva) {

    if (brightness < 20 || viiva.pisteet.empty()) {
        hue += ofRandomf()*0.3;
        return;
    }
    if (viiva.haeUusinPiste().piste.z == 0)
        hue += 0.5;


    if (hue > 360)
        hue = 0;
    if (hue < 0)
        hue = 360;
}

void VariOhjain::laskeSaturation(Viiva& viiva) {
    if (!viiva.pisteet.empty())
        saturation = viiva.haeUusinPiste().tulkinnat.kiihtyvyys * 255;
}

void VariOhjain::laskeBrightness(Viiva& viiva) {
    //brightness = viiva.haeUusinPiste().tulkinnat.vahvuus;
    if (!viiva.pisteet.empty())
        if (saturation < 100)
            brightness -=0.3;
        else
            brightness += 0.9;
    
    if(brightness > 255)
    brightness = 255;
    else if(brightness < 0)
        brightness = 0;
}

ofColor VariOhjain::haeVari() {
    return vari;
}
