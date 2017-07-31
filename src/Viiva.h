#pragma once
#include "ofMain.h"

static float SigmoidFunction(float value) {

    return 1 / (1 + exp(-0.5 * value));

}

struct ViivanTulkinnat {
    float kiihtyvyys;
    float vahvuus;
    float kohoavuus;
    ofPoint paino;

    void muutaTulkintaa(const ViivanTulkinnat& tulkinnat, float maara);
    std::string toString() {return ofToString(kiihtyvyys) +  " " + ofToString(kohoavuus) + " " + ofToString(vahvuus) + " " + ofToString(paino);}
    
private:
    void muutaTulkinta(float& tulkinta, float suunta, float maara);
};

struct ViivanOminaisuudet {
    float nopeus;
    ofVec3f suunta;
    float paine;

    void muutaOminaisuuksia(const ViivanOminaisuudet& ominaisuudet, float maara);
    std::string toString(){return ofToString(nopeus) + " " + ofToString(suunta) + " " + ofToString(paine);}
private:
    void muutaOminaisuus(float& ominaisuus, float suunta, float maara);

};

struct Viiva {
    /* pisteet:
     * x -> hiiren x
     * y -> hiiren y
     * z -> hiiren nappi 1 alaspainettu 0 ylhaalla
     * paine -> piirtopoydan paine
     */

    std::vector<ofPoint> pisteet;
    std::vector<float> paineet;

    ViivanOminaisuudet yleisetOminaisuudet;
    ViivanOminaisuudet hetkellisetOminaisuudet;
    ViivanTulkinnat tulkinnat;

    void tulkitse();
    void laske();


    void asetaYleisetOminaisuudet(const ViivanOminaisuudet& ominaisuudet);


    void lisaaPiste(ofPoint piste, float paine);

    float laskeKeskinopeus(int otanta);
    float laskeKeskipaine(int otanta);
    
    std::string toString();

    float bound(float val, float min, float max) {
        if (val > max)
            return max;
        else if (val < min)
            return min;
        return val;
    }

};

