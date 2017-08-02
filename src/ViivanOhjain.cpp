#include "ViivanOhjain.h"

void ViivanOhjain::setup(int viivaKesken) {
    Sessio::setup(viivaKesken);
    //timedThread::setup(120);
    hidpen::setup(0);
}

void ViivanOhjain::loop() {

    Sessio::update(Hiiri::mouseState.z);


    if (Sessio::moodi == piirtaa) {
        if (hidpen::isOpen) {
            lisaaPiste(Hiiri::mouseState, hidpen::pressure);
        } else {
            // 1 menee joka tapauksessa nollaan ennen pitkaa
            lisaaPiste(Hiiri::mouseState, mouseState.z);
        }
    } else
        tyhjenna();
}

Viiva ViivanOhjain::haeViiva() {    
    return viiva;
}


void ViivanOhjain::lisaaPiste(ofPoint piste, float paine) {
    //tehdään eka piste viivaan koska laskeUusinPiste ja tulkitseUusinPiste muokkaa viimeisintä pistettä 
    viiva.lisaaPiste(piste, paine);

    laskeUusinPiste();
    tulkitseUusinPiste();

}

void ViivanOhjain::tyhjenna() {
    viiva = Viiva();
}

void ViivanOhjain::tulkitseUusinPiste() {
    viiva.haeUusinPiste().tulkinnat.kiihtyvyys += (viiva.haeUusinPiste().hetkellisetOminaisuudet.nopeus - viiva.haeUusinPiste().yleisetOminaisuudet.nopeus)*0.01;
    viiva.haeUusinPiste().tulkinnat.kohoavuus -= sin(viiva.haeUusinPiste().yleisetOminaisuudet.suunta.y)*0.001;
    viiva.haeUusinPiste().tulkinnat.vahvuus = (viiva.haeUusinPiste().yleisetOminaisuudet.paine - viiva.haeUusinPiste().hetkellisetOminaisuudet.paine) -
            (viiva.haeUusinPiste().yleisetOminaisuudet.nopeus - viiva.haeUusinPiste().hetkellisetOminaisuudet.nopeus);
    viiva.haeUusinPiste().tulkinnat.paino = viiva.haeUusinPiste().hetkellisetOminaisuudet.suunta - viiva.haeUusinPiste().yleisetOminaisuudet.suunta;


    viiva.haeUusinPiste().tulkinnat.kiihtyvyys = bound(viiva.haeUusinPiste().tulkinnat.kiihtyvyys, 0, 1);
    viiva.haeUusinPiste().tulkinnat.kohoavuus = bound(viiva.haeUusinPiste().tulkinnat.kohoavuus, 0, 1);
    //tulkinnat.vahvuus = bound(tulkinnat.vahvuus,0,1);

}

void ViivanOhjain::laskeUusinPiste() {

    if (viiva.pisteet.size() > 1) {
        viiva.haeUusinPiste().hetkellisetOminaisuudet.nopeus = bound(laskeKeskinopeus(30)*0.1, 0, 1);
        viiva.haeUusinPiste().hetkellisetOminaisuudet.paine = laskeKeskipaine(30);
        viiva.haeUusinPiste().hetkellisetOminaisuudet.suunta = (ofVec3f) (viiva.pisteet[viiva.pisteet.size() - 1].piste - viiva.pisteet[viiva.pisteet.size() - 2].piste);
    }


    // paivita yleiset ominaisuudet
    if (viiva.pisteet.size() == 2) {
        viiva.haeUusinPiste().yleisetOminaisuudet = viiva.haeUusinPiste().hetkellisetOminaisuudet;
    } else {
        viiva.haeUusinPiste().yleisetOminaisuudet.muutaOminaisuuksia(viiva.haeUusinPiste().hetkellisetOminaisuudet, 0.0005);
    }

}

float ViivanOhjain::laskeKeskinopeus(int otanta) {
    if (viiva.pisteet.empty()) {
        return 0;
    }

    float summa = 0;
    float keskinopeus = 0;
    if (viiva.pisteet.size() < otanta) {
        for (int i = 0; i < viiva.pisteet.size() - 1; i++) {
            summa += (viiva.pisteet[i + 1].piste - viiva.pisteet[i].piste).length();
        }
        keskinopeus = summa / viiva.pisteet.size();
    } else {
        for (int i = viiva.pisteet.size() - otanta; i < viiva.pisteet.size() - 1; i++) {
            summa += (viiva.pisteet[i + 1].piste - viiva.pisteet[i].piste).length();
        }
        keskinopeus = summa / otanta;
    }



    return keskinopeus;
}

float ViivanOhjain::laskeKeskipaine(int otanta) {

    if (viiva.pisteet.empty())
        return 0;

    float summa = 0;
    float keskiherkkyys = 0;

    if (viiva.pisteet.size() < otanta) {
        for (int i = 0; i < viiva.pisteet.size(); i++) {
            summa += viiva.pisteet[i].piste.z;
        }
        keskiherkkyys = summa / viiva.pisteet.size();
    } else {
        for (int i = viiva.pisteet.size() - otanta; i < viiva.pisteet.size(); i++) {
            summa += viiva.pisteet[i].piste.z;
        }
        keskiherkkyys = summa / otanta;
    }
    return keskiherkkyys;
}
