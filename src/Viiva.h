#pragma once
#include "ofMain.h"

static float SigmoidFunction(float value, float herkkyys) {

    return 1 / (1 + exp(-1* herkkyys * value));

}


struct ViivanTulkinnat {
    float kiihtyvyys;
    float vahvuus;
    float kohoavuus;
    float paineenMuutos;
    ofPoint paino;

    ViivanTulkinnat():kiihtyvyys(0),vahvuus(0),kohoavuus(0.5),paineenMuutos(0),paino(ofPoint()) {}
    void muutaTulkintaa(const ViivanTulkinnat& tulkinnat, float maara);

    std::string toString() {
        return ofToString(kiihtyvyys) + " " + ofToString(kohoavuus) + " " + ofToString(vahvuus) + " " + ofToString(paino), + " " + ofToString(paineenMuutos);
    }

private:
    void muutaTulkinta(float& tulkinta, float suunta, float maara);
};

struct ViivanOminaisuudet {
    float nopeus;
    ofVec3f suunta;
    float paine;

    
    void muutaOminaisuuksia(const ViivanOminaisuudet& ominaisuudet, float maara);

    std::string toString() {
        return ofToString(nopeus) + " " + ofToString(suunta) + " " + ofToString(paine);
    }
private:
    void muutaOminaisuus(float& ominaisuus, float suunta, float maara);

};
struct ViivanPiste {
    ofPoint piste;
    float paine;

    ViivanOminaisuudet yleisetOminaisuudet;
    ViivanOminaisuudet hetkellisetOminaisuudet;
    ViivanTulkinnat tulkinnat;
    
    ViivanPiste():piste(ofPoint()),paine(0),yleisetOminaisuudet(ViivanOminaisuudet()),hetkellisetOminaisuudet(ViivanOminaisuudet()),tulkinnat(ViivanTulkinnat()){}

};

struct Viiva {
    /* pisteet:

     * piste:
     * x -> hiiren x
     * y -> hiiren y
     * z -> hiiren nappi 1 alaspainettu 0 ylhaalla
     * paine -> piirtopoydan paine
     */
    ofColor alkuVari;
    std::vector<ViivanPiste> pisteet;

    void lisaaPiste(ofVec3f piste, float paine);
    ViivanPiste& haeUusinPiste();
    const ViivanPiste& haeUusinPiste() const;
    void asetaAlkuVari(ofColor col);
    void asetaYleisetOminaisuudet(const ViivanOminaisuudet& ominaisuudet);
    std::string toString();


};

