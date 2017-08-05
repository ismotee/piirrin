#include "ViivanOhjain.h"

void ViivanOhjain::setup(int viivaKesken) {
    Sessio::setup(viivaKesken);
    //timedThread::setup(120);
    hidpen::setup(0);
    Nauhuri::setup("arkisto/");
    Nauhuri::lataa();
    tila = vapaa;
    viivaOnUusi = true;
}

void ViivanOhjain::loop() {

    Sessio::update(Hiiri::mouseState.z);

    // piirtaa moodi on riippumaton OhjainTilasta. Inputtia ei voi sulkea
    if (moodi == piirtaa) {
        if (hidpen::isOpen) {
            hidpen::update();
            lisaaPiste(Hiiri::mouseState, hidpen::pressure);
        } else {
            cout << "hid not open\n";
            lisaaPiste(Hiiri::mouseState, mouseState.z);
        }
    }

    // Viiva jatetaan tallentamatta jos tila on vapaa. valmistelun tarvii joka tapauksessa tyhjentaa Viiva, jotta voidaan tehda jotain uutta
    if (moodi == valmistelee) {
        if (tila == tallentaa || tila == soittaa) {
            Nauhuri::tallenna(viiva);

        }
        tyhjenna();

        // en tieda pitaisiko soittimen ottaa seuraava vai viimeisin, vai edellinen??
        if (tila == soittaa)
            Nauhuri::seuraava();
    }

    if (moodi == viivaValmis && tila == soittaa) {
        if (Nauhuri::uusiViiva)
            tyhjenna();

        viiva.pisteet.push_back(Nauhuri::soita());
    }
}

Viiva ViivanOhjain::haeViiva() {
    return viiva;
}

void ViivanOhjain::lisaaPiste(ofPoint piste, float paine) {
    //tehdään eka piste viivaan koska laskeUusinPiste ja tulkitseUusinPiste muokkaa viimeisintä pistettä 
    viiva.lisaaPiste(piste, paine);

    laskeUusinPiste();
    tulkitseUusinPiste();
    viivaOnUusi = false;
}

void ViivanOhjain::tyhjenna() {
    viiva = Viiva();
    viivaOnUusi = true;
}

void ViivanOhjain::tulkitseUusinPiste() {
    if (viiva.pisteet.size() > 1) {
        viiva.haeUusinPiste().tulkinnat = viiva.pisteet[viiva.pisteet.size() - 2].tulkinnat;
    }

    float max_nopeus = 50; //px

    float yleinenNopeus = viiva.haeUusinPiste().yleisetOminaisuudet.nopeus;
    float hetkellinenNopeus = viiva.haeUusinPiste().hetkellisetOminaisuudet.nopeus;
    float nopeudenMuutos = (hetkellinenNopeus - yleinenNopeus); // suuruusluokkaa -50...50 -- nopeudesta pikseleinä

    float kiihtyvyys = SigmoidFunction(nopeudenMuutos / max_nopeus, 10); // suuruusluokkaa 0...1

    float yleinenPaine = viiva.haeUusinPiste().yleisetOminaisuudet.paine;
    float hetkellinenPaine = viiva.haeUusinPiste().hetkellisetOminaisuudet.paine;
    float paineenMuutos = SigmoidFunction(hetkellinenPaine - yleinenPaine,5); // välillä -1...1, suuruusluokkaa ~0.1? ei enaa....

    float vahvuus =  paineenMuutos - kiihtyvyys*0.5;

    viiva.haeUusinPiste().tulkinnat.kiihtyvyys = kiihtyvyys;
    viiva.haeUusinPiste().tulkinnat.vahvuus = vahvuus;

    viiva.haeUusinPiste().tulkinnat.kohoavuus -= sin(viiva.haeUusinPiste().yleisetOminaisuudet.suunta.y) * 0.001;
    viiva.haeUusinPiste().tulkinnat.paineenMuutos = paineenMuutos;
    viiva.haeUusinPiste().tulkinnat.paino = viiva.haeUusinPiste().hetkellisetOminaisuudet.suunta - viiva.haeUusinPiste().yleisetOminaisuudet.suunta;

    viiva.haeUusinPiste().tulkinnat.kohoavuus = bound(viiva.haeUusinPiste().tulkinnat.kohoavuus, 0, 1);
    //viiva.haeUusinPiste().tulkinnat.vahvuus = SigmoidFunction(viiva.haeUusinPiste().tulkinnat.vahvuus, 3);

}

void ViivanOhjain::laskeUusinPiste() {

    if (viiva.pisteet.size() > 1) {
        viiva.haeUusinPiste().hetkellisetOminaisuudet.nopeus = laskeKeskinopeus(20);
        viiva.haeUusinPiste().hetkellisetOminaisuudet.paine = laskeKeskipaine(10);
        viiva.haeUusinPiste().hetkellisetOminaisuudet.suunta = (ofVec3f) (viiva.pisteet[viiva.pisteet.size() - 1].piste - viiva.pisteet[viiva.pisteet.size() - 2].piste);
    }


    // paivita yleiset ominaisuudet
    if (viiva.pisteet.size() == 2) {
        viiva.haeUusinPiste().yleisetOminaisuudet = viiva.haeUusinPiste().hetkellisetOminaisuudet;
    } else if (viiva.pisteet.size() > 2) {
        viiva.haeUusinPiste().yleisetOminaisuudet = viiva.pisteet[viiva.pisteet.size() - 2].yleisetOminaisuudet;
        viiva.haeUusinPiste().yleisetOminaisuudet.muutaOminaisuuksia(viiva.haeUusinPiste().hetkellisetOminaisuudet, 0.01);
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
    int lukuja = 0;

    if (viiva.pisteet.size() < otanta) {
        for (int i = 0; i < viiva.pisteet.size(); i++) {
            if (viiva.pisteet[i].paine) {
                summa += viiva.pisteet[i].paine;
                lukuja++;
            }
        }
        if (lukuja)
            keskiherkkyys = summa / lukuja;
    } else {
        for (int i = viiva.pisteet.size() - otanta; i < viiva.pisteet.size(); i++) {
            if (viiva.pisteet[i].paine) {
                summa += viiva.pisteet[i].paine;
                lukuja++;
            }
        }
        if (lukuja)
            keskiherkkyys = summa / lukuja;
    }
    return keskiherkkyys;
}
