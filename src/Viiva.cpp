
#include "Viiva.h"

void ViivanTulkinnat::muutaTulkinta(float& tulkinta, float suunta, float maara) {
    tulkinta = tulkinta * (1 - maara) + suunta * maara;
}

void ViivanTulkinnat::muutaTulkintaa(const ViivanTulkinnat& tulkinnat, float maara) {
    muutaTulkinta(kiihtyvyys, tulkinnat.kiihtyvyys, maara);
    muutaTulkinta(vahvuus, tulkinnat.vahvuus, maara);
    muutaTulkinta(kohoavuus, tulkinnat.kohoavuus, maara);

}

void ViivanOminaisuudet::muutaOminaisuus(float& ominaisuus, float suunta, float maara) {
    ominaisuus = ominaisuus * (1 - maara) + suunta * maara;
}

void ViivanOminaisuudet::muutaOminaisuuksia(const ViivanOminaisuudet& ominaisuudet, float maara) {
    muutaOminaisuus(nopeus, ominaisuudet.nopeus, maara);
    muutaOminaisuus(paine, ominaisuudet.paine, maara);
    suunta.interpolate(ominaisuudet.suunta, maara);
}

void Viiva::tulkitse() {
    tulkinnat.kiihtyvyys += (hetkellisetOminaisuudet.nopeus - yleisetOminaisuudet.nopeus)*0.01;
    tulkinnat.kohoavuus -= sin(yleisetOminaisuudet.suunta.y)*0.001;
    tulkinnat.vahvuus = (yleisetOminaisuudet.paine - hetkellisetOminaisuudet.paine) - (yleisetOminaisuudet.nopeus - hetkellisetOminaisuudet.paine);
    tulkinnat.paino = hetkellisetOminaisuudet.suunta - yleisetOminaisuudet.suunta;


    tulkinnat.kiihtyvyys = bound(tulkinnat.kiihtyvyys,0,1);
    tulkinnat.kohoavuus = bound(tulkinnat.kohoavuus,0,1);
    //tulkinnat.vahvuus = bound(tulkinnat.vahvuus,0,1);

}

void Viiva::laske() {



    if (pisteet.size() > 1) {
        hetkellisetOminaisuudet.nopeus = bound(laskeKeskinopeus(30)*0.1,0,1);
        hetkellisetOminaisuudet.paine = laskeKeskipaine(30);
        hetkellisetOminaisuudet.suunta = (ofVec3f)(pisteet[pisteet.size() - 1] - pisteet[pisteet.size() - 2]);
    }


    // paivita yleiset ominaisuudet
    if (pisteet.size() == 2) {
        yleisetOminaisuudet = hetkellisetOminaisuudet;
    } else {
        yleisetOminaisuudet.muutaOminaisuuksia(hetkellisetOminaisuudet, 0.0005);
    }

}

void Viiva::asetaYleisetOminaisuudet(const ViivanOminaisuudet& ominaisuudet) {
    yleisetOminaisuudet = ominaisuudet;
}

void Viiva::lisaaPiste(ofPoint piste, float paine) {
        pisteet.push_back(piste);
        paineet.push_back(paine);

    laske();
    tulkitse();


    if (pisteet.size() == 2) {
        yleisetOminaisuudet = hetkellisetOminaisuudet;
        tulkinnat.kohoavuus = 0.5;
    } else {
        yleisetOminaisuudet.muutaOminaisuuksia(hetkellisetOminaisuudet, 0.005);
    }

}

float Viiva::laskeKeskinopeus(int otanta) {
    if (pisteet.empty()) {
        return 0;
    }

    float summa = 0;
    float keskinopeus = 0;
    if (pisteet.size() < otanta) {
        for (int i = 0; i < pisteet.size() - 1; i++) {
            summa += (pisteet[i + 1] - pisteet[i]).length();
        }
        keskinopeus = summa / pisteet.size();
    } else {
        for (int i = pisteet.size() - otanta; i < pisteet.size() - 1; i++) {
            summa += (pisteet[i + 1] - pisteet[i]).length();
        }
        keskinopeus = summa / otanta;
    }



    return keskinopeus;
}

float Viiva::laskeKeskipaine(int otanta) {

    if (pisteet.empty())
        return 0;

    float summa = 0;
    float keskiherkkyys = 0;

    if (pisteet.size() < otanta) {
        for (int i = 0; i < pisteet.size(); i++) {
            summa += pisteet[i].z;
        }
        keskiherkkyys = summa / pisteet.size();
    } else {
        for (int i = pisteet.size() - otanta; i < pisteet.size(); i++) {
            summa += pisteet[i].z;
        }
        keskiherkkyys = summa / otanta;
    }
    return keskiherkkyys;
}

std::string Viiva::toString() {
    std::string result;

    result += "tulkinnat: " + tulkinnat.toString() + "\nyleiset: " + yleisetOminaisuudet.toString() + "\nhetkelliset: " + hetkellisetOminaisuudet.toString();
    return result;

}
