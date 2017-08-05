#include "tiedosto.h"
#include <iterator>
#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>

Viiva tiedosto::lataaViiva(std::string tiedostonNimi) {
    std::ifstream is(tiedostonNimi, ios::binary | ios::ate | ios::in);
    Viiva viiva;

    if (is.is_open()) {

        char* memory;
        streampos size = is.tellg();
        size_t pisteSize = (size - sizeof (ofColor)) / sizeof (ViivanPiste);
        cout << pisteSize/sizeof(ViivanPiste) << "\n";
        is.seekg(0, ios::beg);
        memory = new char[size];

        is.read(memory, size);
        ofColor* col = (ofColor*) memory;
        viiva.alkuVari = (*col);
        cout << "testi\n";
        for (int i = 0; i < pisteSize; i++) {
            ViivanPiste* vp;
            vp = (ViivanPiste*) (sizeof (ofColor) + memory + (i * sizeof (ViivanPiste)));
            viiva.pisteet.push_back((*vp));
        }

        is.close();

        delete[] memory;
    }
    return viiva;
}

std::string tiedosto::aika() {
    std::chrono::time_point<std::chrono::system_clock> now;
    now = std::chrono::system_clock::now();
    std::time_t now_t = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&now_t);

}

void tiedosto::tallennaViiva(Viiva viiva, std::string polku) {
    std::string file = polku + aika() + ".ov";
    std::ofstream os(file, ios::binary);

    char* colorBuffer;
    colorBuffer = (char*) &viiva.alkuVari;
    os.write( colorBuffer, sizeof (ofColor));

    for (ViivanPiste& piste : viiva.pisteet) {

        char* buffer;
        buffer = (char*) &piste;
        os.write((char*) buffer, sizeof (ViivanPiste));
    }

    os.close();
}

