#include "Nauhuri.h"

void Nauhuri::setup(std::string polku_) {
    polku = polku_;
    lukuPaa = 0;
    viivaId = 0;
}

void Nauhuri::lataa() {

    dir.listDir(polku);
    db.clear();
    db.resize(dir.size());

    for (int i = 0; i < dir.size(); i++) {
        cout << dir.getPath(i) << "\n";
        db[i] = tiedosto::lataaViiva("bin/data/" + dir.getPath(i));
    }
}

void Nauhuri::tallenna(Viiva viiva) {
    tiedosto::tallennaViiva(viiva, "bin/data/" + polku);
    lataa();
}

ViivanPiste Nauhuri::soita() {
    
    ViivanPiste result;
    
    if (!db.empty() && !db[viivaId].pisteet.empty()) {
        uusiViiva = false;
        result = db[viivaId].pisteet[(int) lukuPaa];
        lukuPaa++;
        if (lukuPaa >= db[viivaId].pisteet.size()) {
            seuraava();
        }
        
    }
    return result;
}

void Nauhuri::pause() {

}

void Nauhuri::edellinen() {
    if (!db.empty()) {
        lukuPaa = 0;
        viivaId--;
        if (viivaId < 0)
            viivaId = db.size() - 1;
    } else
        viivaId = 0;
    uusiViiva = true;
}

void Nauhuri::seuraava() {
    lukuPaa = 0;
    viivaId++;
    if (viivaId >= db.size())
        viivaId = 0;
    uusiViiva= true;
}
