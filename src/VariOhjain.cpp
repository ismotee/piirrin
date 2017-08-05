
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
        hue += 0.3;


    if (hue > 255)
        hue = 0;
    if (hue < 0)
        hue = 255;
}

void VariOhjain::laskeSaturation(Viiva& viiva) {
    if (!viiva.pisteet.empty()) {
        saturation += (viiva.haeUusinPiste().tulkinnat.kiihtyvyys-0.5)*3+0.01;
        saturation +=  (viiva.haeUusinPiste().hetkellisetOminaisuudet.paine - 0.5) * 255 * 0.001;
        
    }
    else
        saturation = 255;

    saturation = ofClamp(saturation,0,355);
}

void VariOhjain::laskeBrightness(Viiva& viiva) {
    //brightness = viiva.haeUusinPiste().tulkinnat.vahvuus;

    if (!viiva.pisteet.empty()) {
        //brightness +=  (1.05-viiva.haeUusinPiste().tulkinnat.paineenMuutos)*1.9;
        float brightnessMuutos = 255-(1/0.75)*255 *viiva.haeUusinPiste().tulkinnat.vahvuus;
        cout << brightnessMuutos << "\n";
        brightness = brightness *0.95+ brightnessMuutos*0.05;
    }
    else
        brightness += 0.9;

    if (brightness > 255)
        brightness = 255;
    else if (brightness < 5)
        brightness = 5;
}

ofColor VariOhjain::haeVari() {
    return vari;
}

void VariOhjain::asetaVari(ofColor col) {
    vari = col;
    vari.getHsb(hue, saturation, brightness);
    vari.setSaturation(255);
}
