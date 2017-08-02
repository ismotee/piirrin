
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


void Viiva::asetaYleisetOminaisuudet(const ViivanOminaisuudet& ominaisuudet) {
    haeUusinPiste().yleisetOminaisuudet = ominaisuudet;
}




void Viiva::lisaaPiste(ofPoint piste, float paine) {
        pisteet.push_back(ViivanPiste());
        haeUusinPiste().piste = piste;
        haeUusinPiste().paine = paine;

}


std::string Viiva::toString() {
    std::string result;

    result += "tulkinnat: " + haeUusinPiste().tulkinnat.toString() + "\nyleiset: " + haeUusinPiste().yleisetOminaisuudet.toString() + "\nhetkelliset: " + haeUusinPiste().hetkellisetOminaisuudet.toString();
    return result;

}

ViivanPiste& Viiva::haeUusinPiste() {
    //TODO tyhjän vectorin tsekkaukset
    return pisteet.back();
}
