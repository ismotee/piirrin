#include "nauhuri.h"

void nauhuri::setup(std::string polku_) {
    polku = polku_;



}

void nauhuri::lataa() {

    dir.listDir(polku);
    
}

void nauhuri::tallenna() {

}

void nauhuri::soita() {

}

void nauhuri::pause() {

}

void nauhuri::asetaNykyinenViiva(Viiva viiva) {
    nykyinenViiva = viiva;
}

void nauhuri::edellinen() {

}

void nauhuri::seuraava() {

}
